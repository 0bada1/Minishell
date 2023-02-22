/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:28:56 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/20 22:07:43 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*raw_lexer(t_shell_s *minishell, char *str)
{
	t_counter	count;
	
	if (!str)
		return (minishell);
	minishell->lexer->raw_tokens = malloc(sizeof(char *) * (num_of_tokens(str) + 1));
	count.i = skip_spaces(str, 0);
	count.j = 0;
	while (str[count.i])
	{
		count.k = 0;
		if (str[count.i] == '\"')
		{
			while (str[count.i])
			{
				minishell->lexer->raw_tokens[count.j][count.k++] = str[count.i];
				if (str[count.i] == '\"' && (str[count.i + 1] && (str[count.i + 1] == ' ' || str[count.i + 1] == '\t')))
					break;
				count.i++;
			}
		}
		else
		{
			
		}
		count.i++;
	}
	for (int i = 0; minishell->lexer->raw_tokens[i]; i++)
		printf("raw_token[%i]: %s\n", i, minishell->lexer->raw_tokens[i]);
	return (minishell);
}

int	raw_token_size(char *str, int i)
{
	int	length;
	
	if (!str)
		return (0);
	length = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		if (str[i] == '\"')
		{
			while (str[i])
			{
				if (str[i] == '\"' && (str[i + 1] && (str[i + 1] == ' ' || str[i + 1] == '\t')))
					break;
				i++;
				length++;
			}
		}
	}
	return (length);
}

// char	**split_pipes(char	*str)
// {
// 	char	**blocks;
// 	t_counter	count;

// 	if (!str)
// 		return (NULL);
// 	count.i = 0;
// 	count.j = 0;
// 	blocks = malloc(sizeof(char *) * (count_pipes(str) + 2));
// 	printf("count_pipes = %i\n", count_pipes(str));
// 	while (str[count.i])
// 	{
// 		blocks[count.j] = malloc(sizeof(char) * length_to_pipe(str, count.i) + 1);
// 		count.trigger = 0;
// 		count.k = 0;
// 		while (str[count.i])
// 		{
// 			if (str[count.i] == '\"')
// 			{
// 				blocks[count.j][count.k++] = str[count.i++];
// 				while (str[count.i] && str[count.i] != '\"' && ((!str[count.i + 1]) || (str[count.i + 1] && str[count.i + 1] != ' ' && str[count.i + 1] != '\t')))
// 					blocks[count.j][count.k++] = str[count.i++];
// 				blocks[count.j][count.k++] = str[count.i++];
// 				count.trigger = 1;
// 			}
// 			if (str[count.i] == '|')
// 			{
// 				count.i++;
// 				count.i = skip_spaces(str, count.i);
// 				break;
// 			}
// 			if (count.trigger == 0)
// 				blocks[count.j][count.k++] = str[count.i++];
// 		}
// 		blocks[count.j++][count.k] = '\0';
// 		// if (count.trigger % 2 == 0 && (str[count.i + 1] && ((!str[count.i + 1]) || (str[count.i + 1] == ' ' || str[count.i + 1] == '\t'))))
// 		// 	break;
// 	}
// 	blocks[count.j] = NULL;
// 	printf("Printing blocks\n");
// 	for (int i = 0; i < count_pipes(str) + 1; i++)
// 	{
// 		printf("block[%i]: %s\n", i, blocks[i]);
// 	}
// 	return (blocks);
// }

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