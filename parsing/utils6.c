/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:28:56 by ooutabac          #+#    #+#             */
/*   Updated: 2023/03/05 14:15:19 by ooutabac         ###   ########.fr       */
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
	// printf("num of tokens = %i\n", minishell->lexer->num_of_tokens);
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
			// printf("This is a heredoc\n");
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
	// for (int i = 0; minishell->lexer->raw_tokens[i]; i++)
	// 	printf("raw_tokens[%i] = %s\n", i, minishell->lexer->raw_tokens[i]);
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
	blocks = ft_calloc(sizeof(char *), count_pipes(str) + 2);
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
	blocks[count.j] = NULL;
	// for (int i = 0; blocks[i]; i++)
		// printf("block[%i] = %s\n", i, blocks[i]);
	return (blocks);
}

int	num_of_tokens_to_pipe(char **tokens, int token_num)
{
	t_counter	count;
	
	if (!tokens || !tokens[0])
		return (0);
	count.i = 0;
	count.counter = 0;
	while (tokens[token_num])
	{
		if (ft_strncmp(tokens[token_num], "|\0", 2) == 0)
			break ;
		count.counter++;
		token_num++;
	}
	// printf("num of tokens till pipe = %i\n", count.counter);
	return (count.counter);
}

char	**split_raw_command_block(t_shell_s *minishell, int token_num)
{
	t_counter	count;
	char		**command_block;

	if (!minishell || !minishell->lexer || !minishell->lexer->tokens)
		return (NULL);
	count.i = 0;
	count.j = 0;
	command_block = ft_calloc(sizeof(char *), num_of_tokens_to_pipe(minishell->lexer->raw_tokens, token_num) + 1);
	while (minishell->lexer->raw_tokens[token_num] && ft_strncmp(minishell->lexer->raw_tokens[token_num], "|\0", 2) != 0)
	{
		command_block[count.i] = ft_strdup(minishell->lexer->raw_tokens[token_num]);
		count.i++;
		token_num++;
	}
	return (command_block);
}

char	**split_command_block(t_shell_s *minishell, int token_num)
{
	t_counter	count;
	char		**command_block;

	if (!minishell || !minishell->lexer || !minishell->lexer->tokens)
		return (NULL);
	count.i = 0;
	count.j = 0;
	command_block = ft_calloc(sizeof(char *), num_of_tokens_to_pipe(minishell->lexer->raw_tokens, token_num) + 1);
	while (minishell->lexer->tokens[token_num] && ft_strncmp(minishell->lexer->raw_tokens[token_num], "|\0", 2) != 0)
	{
		command_block[count.i] = ft_strdup(minishell->lexer->tokens[token_num]);
		count.i++;
		token_num++;
	}
	return (command_block);
}
// char	**split_command_block(char	*str)
// {
// 	t_counter	count;
// 	char		**command_block;

// 	if (!str)
// 		return (NULL);
// 	count.i = 0;
// 	count.j = 0;
// 	count.k = 0;
// 	command_block = ft_calloc(sizeof(char *), (count_tokens(str) + 1));
// 	printf("number of tokens in split_command_block = %i\n", count_tokens(str));
// 	while (str[count.i])
// 	{
// 		count.k = 0;
// 		command_block[count.j] = malloc(sizeof(char) * (token_size(str, count.i) + 1));
// 		printf("token size in split_command_block = %i\n", token_size(str, count.i));
// 		while (str[count.i] && str[count.i] != ' ' && str[count.i] != '\t')
// 		{
// 			if (str[count.i] == '\"')
// 			{
// 				command_block[count.j][count.k++] = str[count.i++];
// 				while (str[count.i] && str[count.i] != '\"')
// 					command_block[count.j][count.k++] = str[count.i++];
// 				command_block[count.j][count.k++] = str[count.i++];
// 			}
// 			else if (str[count.i] == '\'')
// 			{
// 				command_block[count.j][count.k++] = str[count.i++];
// 				while (str[count.i] && str[count.i] != '\'')
// 					command_block[count.j][count.k++] = str[count.i++];
// 				command_block[count.j][count.k++] = str[count.i++];
// 			}
// 			else if (str[count.i] != ' ' && str[count.i] != '\t')
// 				command_block[count.j][count.k++] = str[count.i++];
// 		}
// 			command_block[count.j][count.k] = '\0';
// 			count.i = skip_spaces(str, count.i);
// 			count.j++;
// 	}
// 	command_block[count.j] = NULL;
// 	for (int i = 0; command_block[i]; i++)
// 		printf("command_block[%i] in split_command_block = %s\n", i, command_block[i]);
// 	return (command_block);
// }

// length and i are the same number so use one
int	length_to_pipe(char *str, int i)
{
	int	length;
	int	trigger;

	if (!str)
		return (0);
	length = 0;
	// printf("i = %i\n", i);
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
	// printf("length to pipe = %i\n", length);
	return (length);
}