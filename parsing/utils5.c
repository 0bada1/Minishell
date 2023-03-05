/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:29:08 by ooutabac          #+#    #+#             */
/*   Updated: 2023/03/02 20:40:01 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_if_command(t_shell_s *minishell, char *token, int	token_num)
{
	if (!minishell || !token)
		return (FALSE);
	if (ft_strncmp(token, ">\0", 2) == 0 || ft_strncmp(token, "<\0", 2) == 0 || ft_strncmp(token, "|\0", 2) == 0 || ft_strncmp(token, ">>\0", 3) == 0 || ft_strncmp(token, "<<\0", 3) == 0)
		return (FALSE);
	if (token_num > 0 && (ft_strncmp(minishell->lexer->raw_tokens[token_num - 1], ">\0", 2) == 0 || ft_strncmp(minishell->lexer->raw_tokens[token_num - 1], "<\0", 2) == 0 || ft_strncmp(minishell->lexer->raw_tokens[token_num - 1], "<<\0", 3) == 0 || ft_strncmp(minishell->lexer->raw_tokens[token_num - 1], ">>\0", 3) == 0))
		return (FALSE);
	return (TRUE);
}

// int	check_validity(t_shell_s *minishell)
// {
// 	t_counter	count;
// 	char		*token;

// 	count.i = 0;
// 	count.trigger = 0;
// 	while (minishell->lexer->tokens[count.i])
// 	{
// 		token = ft_strdup(minishell->lexer->tokens[count.i]);
// 		if (token == '>' || token == '<' || token == '\"' || token == '\'' || token == '|' || token == '$')
// 		{
// 			count.trigger = 1;
// 		}
// 		free(token);
// 		count.i++;
// 	}
// 	return (TRUE);
// }

int	get_num_flags(char **token, int i)
{
	t_counter	count;

	if (!token)
		return (0);
	count.counter = 0;
	while (token[i])
	{
		if ((ft_strncmp(token[i], ">\0", 2) == 0 || ft_strncmp(token[i], "<\0", 2) == 0 || ft_strncmp(token[i], "<<\0", 3) == 0 || ft_strncmp(token[i], ">>\0", 3) == 0))
			i++;
		else if (ft_strncmp(token[i], "|\0", 2) != 0)
			count.counter++;
		else if (ft_strncmp(token[i], "|\0", 2) == 0)
			break ;
		i++;
	}
	// printf("num of args = %i\n", count.counter);
	return (count.counter);
}

/* CHECK_VALIDITY
- Function to check for syntax error
* CASES
minishell$ < | (Redirection before pipe)
minishell$ > | (Redirection before pipe)
minishell$ < (Redirection with nothing after)
minishell$ | (Pipe with nothing after or before)
minishell$ | | (Pipe with pipe after)
minishell$ < < (Redirection with redirection after)
minishell$ > > (Redirection with redirection after)
minishell$ < > (Redirection with redirection after)
minishell$ > < (Redirection with redirection after)
minishell$ <> (2 redirections in the same token)
minishell$ >< (2 redirections in the same token)
minishell$ cat '<' infile (Not valid redirection if in quotes)
*/
int	check_validity(t_shell_s *minishell, char *str)
{
	t_counter	count;

	if (!str || !str[0])
		return (TRUE);
	if (!minishell || !minishell->lexer || !minishell->lexer->raw_tokens || !minishell->lexer->raw_tokens[0])
		return (FALSE);
	count.i = 0;
	count.j = 0;
	if (minishell->lexer->raw_tokens && ft_strncmp(minishell->lexer->raw_tokens[0], "|", 2) == 0)
		return (FALSE);
	while (minishell->lexer->raw_tokens[count.i])
	{
		// Redirection before pipe
		if (minishell->lexer->raw_tokens[count.i + 1] && ft_strncmp(minishell->lexer->raw_tokens[count.i + 1], "|\0", 2) == 0 && (ft_strncmp(minishell->lexer->raw_tokens[count.i], ">", 2) == 0 || ft_strncmp(minishell->lexer->raw_tokens[count.i], "<", 2) == 0))
			return (FALSE);
		// Nothing after a redirection
		if ((ft_strncmp(minishell->lexer->raw_tokens[count.i], ">\0", 2) == 0 || ft_strncmp(minishell->lexer->raw_tokens[count.i], "<\0", 2) == 0) && !minishell->lexer->raw_tokens[count.i + 1])
			return (FALSE);
		// 2 redirections of different types
		if (ft_strncmp(minishell->lexer->raw_tokens[count.i], "<\0", 2) == 0 && ft_strncmp(minishell->lexer->raw_tokens[count.i + 1], ">\0", 2) == 0)
			return (FALSE);
		if (ft_strncmp(minishell->lexer->raw_tokens[count.i], ">\0", 2) == 0 && ft_strncmp(minishell->lexer->raw_tokens[count.i + 1], "<\0", 2) == 0)
			return (FALSE);
		if (ft_strncmp(minishell->lexer->raw_tokens[count.i], ">\0", 2) == 0 && ft_strncmp(minishell->lexer->raw_tokens[count.i + 1], ">\0", 2) == 0)
			return (FALSE);
		if (ft_strncmp(minishell->lexer->raw_tokens[count.i], "<\0", 2) == 0 && ft_strncmp(minishell->lexer->raw_tokens[count.i + 1], "<\0", 2) == 0)
			return (FALSE);
		if (ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) == 0 && !minishell->lexer->raw_tokens[count.i + 1])
			return (FALSE);
		if (ft_strncmp(minishell->lexer->raw_tokens[count.i], "|\0", 2) == 0 && ft_strncmp(minishell->lexer->raw_tokens[count.i + 1], "|\0", 2) == 0)
			return (FALSE);
		// if (ft_strncmp(minishell->lexer->raw_tokens[count.i], "|", 2))
		count.i++;
	}
	// while (minishell->lexer->command_blocks[count.j])
	// {
	// 	if (!minishell->lexer->command_blocks[count.j] && minishell->lexer->command_blocks[count.j + 1])
	// 		return (FALSE);
	// 	count.j++;
	// }
	return (TRUE);
}