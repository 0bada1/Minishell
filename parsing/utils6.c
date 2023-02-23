/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:28:56 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/23 22:01:01 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*raw_lexer(t_shell_s *minishell, char *str)
{
	t_counter	count;

	if (!minishell)
		return (NULL);
	if (!str)
		return (minishell);
	count.i = 0;
	count.j = 0;
	minishell->lexer->raw_tokens = malloc(sizeof(char *) * (minishell->lexer->num_of_tokens + 1));
	printf("num of tokens = %i\n", minishell->lexer->num_of_tokens);
	while (str[count.i] && count.j < minishell->lexer->num_of_tokens)
	{
		minishell->lexer->raw_tokens[count.j] = malloc(sizeof(char) * raw_token_size(str, count.i) + 1);
		count.k = 0;
		count.trigger = 0;
		while (str[count.i] && count.j < minishell->lexer->num_of_tokens)
		{
			if (str[count.i] == '\"')
			{
				minishell->lexer->raw_tokens[count.j][count.k++] = str[count.i++];
				while (str[count.i] && str[count.i] != '\"')
				{
					minishell->lexer->raw_tokens[count.j][count.k++] = str[count.i++];
				}
				minishell->lexer->raw_tokens[count.j][count.k++] = str[count.i++];
			}
			else if (str[count.i] == '\'')
			{
				minishell->lexer->raw_tokens[count.j][count.k++] = str[count.i++];
				while (str[count.i] && str[count.i] != '\'')
				{
					minishell->lexer->raw_tokens[count.j][count.k++] = str[count.i++];
				}
				minishell->lexer->raw_tokens[count.j][count.k++] = str[count.i++];
			}
			else if (str[count.i] == '<' || str[count.i] == '>' || str[count.i] == '|')
			{
				break ;
			}
			else if (str[count.i] != ' ' && str[count.i] != '\t')
			{
				minishell->lexer->raw_tokens[count.j][count.k++] = str[count.i++];
			}
			else if (str[count.i] == ' ' || str[count.i] == '\t')
				break ;
			// printf("%c", str[count.i]);
		}
		if (count.k > 0)
			minishell->lexer->raw_tokens[count.j++][count.k] = '\0';
		if ((str[count.i] == '>' && str[count.i + 1] && str[count.i + 1] == '>') || (str[count.i] == '<' && str[count.i + 1] && str[count.i + 1] == '<'))
		{
			printf("This is a heredoc\n");
			minishell->lexer->raw_tokens[count.j] = malloc(sizeof(char) * (3));
			minishell->lexer->raw_tokens[count.j][0] = str[count.i];
			minishell->lexer->raw_tokens[count.j][1] = str[count.i + 1];
			minishell->lexer->raw_tokens[count.j++][2] = '\0';
			count.i = skip_symbols(str, count.i);
		}
		else if (str[count.i] == '>' || str[count.i] == '<' || str[count.i] == '|')
		{
			minishell->lexer->raw_tokens[count.j] = malloc(sizeof(char) * (2));
			minishell->lexer->raw_tokens[count.j][0] = str[count.i];
			minishell->lexer->raw_tokens[count.j++][1] = '\0';
			count.i = skip_symbols(str, count.i);
		}
		count.i = skip_spaces(str, count.i);
		// printf("str[%i] = %c\n", count.i, str[count.i]);
	}
	minishell->lexer->raw_tokens[count.j] = NULL;
	for (int i = 0; minishell->lexer->raw_tokens[i]; i++)
		printf("raw_tokens[%i] = %s\n", i, minishell->lexer->raw_tokens[i]);
	return (minishell);
}

int	raw_token_size(char *str, int i)
{
    int length;
	int	trigger;

    if (!str)
        return (0);
    length = 0;
    i = skip_spaces(str, i);
    while (str[i] && (str[i] != ' ' && str[i] != '\t'))
    { 
		trigger = 0;
		if (str[i] == '\'')
		{
			i++;
			length++;
			while (str[i] && str[i] != '\'')
			{
				length++;
				i++;
			}
			trigger = 1;
			length++;
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			length++;
			while (str[i] && str[i] != '\"')
			{
				length++;
				i++;
			}
			trigger = 1;
			length++;
			i++;
		}
		if (length == 0 && ((str[i] == '>' && str[i + 1] && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] && str[i + 1] == '<')))
			return (2);
		else if (length != 0 && ((str[i] == '>' && str[i + 1] && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] && str[i + 1] == '<')))
			return (length);
		if (length == 0 && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
			return (1);
		else if (length != 0 && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
			return (length);
		if (trigger == 0)
		{
        	length++;
        	i++;
		}
    }
	// printf("token size = %i\n", length);
    return (length);
}

char	**split_pipes(char	*str)
{
	char		**blocks;
	t_counter	count;

	if (!str || !str[0])
		return (NULL);
	count.i = 0;
	count.j = 0;
	blocks = ft_calloc(sizeof(char *), count_pipes(str) + 1);
	if (!blocks)
		return (NULL);
	while (str[count.i])
	{
		count.trigger = 0;
		count.k = 0;
		blocks[count.j] = ft_calloc(sizeof(char), length_to_pipe(str, count.i) + 1);
		while (str[count.i])
		{
			if (str[count.i] == '\"')
			{
				blocks[count.j][count.k++] = str[count.i++];
				while (str[count.i] && str[count.i] != '\"')
					blocks[count.j][count.k++] = str[count.i++];
				blocks[count.j][count.k++] = str[count.i++];
			}
			else if (str[count.i] == '\'')
			{
				blocks[count.j][count.k++] = str[count.i++];
				while (str[count.i] && str[count.i] != '\'')
					blocks[count.j][count.k++] = str[count.i++];
				blocks[count.j][count.k++] = str[count.i++];
			}
			else if (str[count.i] == '|' && count.trigger == 0)
			{
				count.i++;
				count.i = skip_spaces(str, count.i);
				break;
			}
			else
				blocks[count.j][count.k++] = str[count.i++];
		}
		blocks[count.j++][count.k] = '\0';
	}
	// printf("block[%i] = %s\n", count.j, blocks[0]);
	blocks[count.j] = NULL;
	for (int i = 0; blocks[i]; i++)
		printf("block[%i] = %s\n", i, blocks[i]);
	return (blocks);
} 

int	length_to_pipe(char *str, int i)
{
	int	length;
	int	trigger;

	if (!str)
		return (0);
	length = 0;
	printf("i = %i\n", i);
	while (str[i])
	{
		trigger = 0;
		if (str[i] == '\"')
		{
			i++;
			length++;
			while (str[i] && str[i] != '\"')
			{
				length++;
				i++;
			}
			length++;
			i++;
			trigger = 1;
		}
		else if (str[i] == '\'')
		{
			i++;
			length++;
			while (str[i] && str[i] != '\'')
			{
				length++;
				i++;
			}
			i++;
			length++;
			trigger = 1;
		}
		if (str[i] == '|' && trigger == 0)
				break;
		if (trigger == 0)
		{
			i++;
			length++;
		}
	}
	printf("length to pipe = %i\n", length);
	return (length);
}