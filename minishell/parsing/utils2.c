/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:57 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/13 18:11:43 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*get_path(t_shell_s *minishell, char **envp)
{
	t_counter	count;

	count.i = 0;
	while (envp[count.i] != NULL)
	{
		if (ft_strnstr(envp[count.i++], "PATH=", 5))
		{
			minishell->path = ft_split(envp[count.i - 1] + 5, ':');
			break ;
		}
	}
	return (minishell);
}

t_shell_s	*get_home(t_shell_s *minishell, char **envp)
{
	t_counter	count;

	count.i = 0;
	while (envp[count.i] != NULL)
	{
		if (ft_strnstr(envp[count.i++], "HOME=", 5))
		{
			minishell->home = ft_strdup(envp[count.i - 1] + 5);
			break ;
		}
	}
	return (minishell);
}

// t_shell_s	*get_commands(t_shell_s *minishell, char *str)
// {
// 	t_counter	count;

// 	count.i = 0;
// 	count.j = 0;
// 	count.k = 0;
// 	count.m = 0;
// 	count.trigger = 0;
// 	if (!str || !minishell || !minishell->lexer)
// 		return (minishell);
// 	minishell = get_num_commands(minishell, str);
// 	minishell->commands = ft_calloc(sizeof(char *), (minishell->num_commands + 1));
// 	minishell->flags = malloc(sizeof(char **) * (minishell->num_commands + 1));
// 	while (minishell->lexer->tokens[count.i])
// 	{
// 		count.trigger = 0;
// 		if (ft_strncmp(minishell->lexer->tokens[count.i], "|", 2) != 0)
// 			count.trigger = 1;
// 		if ()
// 		if (check_if_command(minishell, minishell->lexer->tokens[count.i]) == TRUE && count.trigger == 1)
// 			minishell->commands[count.j++] = ft_strdup(minishell->lexer->tokens[count.i]);
		
// 	}
// 	minishell->commands[count.j] = NULL;
// 	for (int i = 0; i < minishell->num_commands; i++)
// 		printf("command[%i] = %s\n", i, minishell->commands[i]);
// 	return (minishell);
// }

t_shell_s	*get_num_commands(t_shell_s *minishell, char *str)
{
	t_counter	count;
	
	count.i = 0;
	count.trigger = 0;
	count.counter = 0;
	if (!str)
		return (minishell);
	while (minishell->lexer->tokens[count.i])
	{
		count.trigger = 0;
		if (ft_strncmp(minishell->lexer->tokens[count.i], "|", 2) == 0 && minishell->lexer->tokens[count.i + 1])
		{
			count.i++;
			count.trigger = 1;
		}
		// printf("count.i = %i\n", count.i);
		if (minishell->lexer->tokens[count.i][0] == '>' || minishell->lexer->tokens[count.i][0] == '<')
		{
			if (minishell->lexer->tokens[count.i + 1])
				count.i += 2;
			else
			{
				minishell->num_commands = count.counter;
				return (minishell);
			}
		}
		else if (count.i == 0 || count.trigger == 1)
		{
			count.counter++;
		}
		count.i++;
	}
	minishell->num_commands = count.counter;
	printf("number of commands = %i\n", minishell->num_commands);
	return (minishell);
}
//  && minishell->lexer->tokens[count.i + 2]