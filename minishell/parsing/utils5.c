/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:29:08 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/10 17:33:23 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_if_command(t_shell_s *minishell, char *token)
{
	t_counter	count;

	if (!minishell || !token)
		return (FALSE);
	count.i = 0;
	while (token[count.i])
	{
		if (token[count.i] == '>' || token[count.i] == '<' || token[count.i] == '\"' || token[count.i] == '\'' || token[count.i] == '|' || token[count.i] == '$')
			return (FALSE);
		count.i++;
	}
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