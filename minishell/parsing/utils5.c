/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:29:08 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/13 18:43:54 by ooutabac         ###   ########.fr       */
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

int	get_num_flags(char **token, int i)
{
	t_counter	count;

	if (!token)
		return (0);
	count.counter = 0;
	while (token[i])
	{
		if (ft_strncmp(token[i], "|", 2) != 0)
			count.counter++;
		else
			break ;
		i++;
	}
	printf("num of args = %i\n", count.counter);
	return (count.counter);
}