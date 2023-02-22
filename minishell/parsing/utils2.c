/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:57 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/21 13:49:15 by ooutabac         ###   ########.fr       */
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

t_shell_s	*get_env_struct(t_shell_s *minishell, char *envp[])
{
	t_counter	count;
	if (!minishell)
		return (NULL);
	count.i = 0;
	while (envp[count.i])
		count.i++;
	minishell->envp.env_size = count.i;
	// printf("envp[%i] = %s\n", count.i, envp[count.i - 1]);
	minishell->envp.envp = malloc(sizeof(char *) * count.i + 1);
	minishell->envp.key = malloc(sizeof(char *) * count.i + 1);
	minishell->envp.value = malloc(sizeof(char *) * count.i + 1);
	count.i = 0;
	while (envp[count.i])
	{
		count.j = 0;
		minishell->envp.envp[count.i] = ft_strdup(envp[count.i]);
		minishell->envp.key[count.i] = malloc(sizeof(char) * ft_strlen_equals(envp[count.i]) + 1);
		while (envp[count.i][count.j] && envp[count.i][count.j] != '=')
		{
			minishell->envp.key[count.i][count.j++] = envp[count.i][count.j];
		}
		minishell->envp.key[count.i][count.j++] = envp[count.i][count.j];
		minishell->envp.key[count.i][count.j] = '\0';
		minishell->envp.value[count.i] = ft_strchr(envp[count.i], '=') + 1;
		// printf("key[%i] = %s\nvalue[%i] = %s\n", count.i, minishell->envp.key[count.i], count.i, minishell->envp.value[count.i]);
		count.i++;
	}
	// printf("\n\n\n");
	// printf("envp[%i] = %s\n", count.i, envp[count.i - 1]);
	// minishell->envp.envp[count.i] = NULL;
	return (minishell);
}

t_shell_s	*get_command_blocks(t_shell_s *minishell, char *str)
{
	t_counter	count;

	if (!str)
		return (minishell);
	count.i = 0;
	while (str[count.i])
	{
		count.i++;
	}
	return (minishell);
}

t_shell_s	*get_commands(t_shell_s *minishell, char *str)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	if (!str || !minishell || !minishell->lexer)
		return (minishell);
	minishell = get_num_commands(minishell, str);
	minishell->commands = ft_calloc(sizeof(char *), (minishell->num_commands + 1));
	minishell->flags = malloc(sizeof(char **) * (minishell->num_commands + 1));
	while (minishell->lexer->tokens[count.i])
	{
		count.k = 0;
		if (check_if_command(minishell, minishell->lexer->tokens[count.i]) == TRUE)
		{
			minishell->commands[count.j] = ft_strdup(minishell->lexer->tokens[count.i]);
			minishell->flags[count.j] = ft_calloc(sizeof(char *), get_num_flags(minishell->lexer->tokens, count.i) + 1);
			while (minishell->lexer->tokens[count.i] && ft_strncmp(minishell->lexer->tokens[count.i], "|", 2) != 0)
				minishell->flags[count.j][count.k++] = ft_strdup(minishell->lexer->tokens[count.i++]);
			minishell->flags[count.j++][count.k] = NULL;
		}
		while (minishell->lexer->tokens[count.i] && ft_strncmp(minishell->lexer->tokens[count.i], "|", 2) != 0)
			count.i++;
		if (minishell->lexer->tokens[count.i] && ft_strncmp(minishell->lexer->tokens[count.i], "|", 2) == 0)
			count.i++;
	}
	minishell->commands[count.j] = NULL;
	// for (int i = 0; i < minishell->num_commands; i++)
	// 	printf("command[%i] = %s\n", i, minishell->commands[i]);
	// for (int k = 0; k < minishell->num_commands; k++)
	// 	for (int j = 0; j < get_num_flags(minishell->lexer->tokens, k) - 1; j++)
	// 		printf("args[%i] = %s\n", j, minishell->flags[k][j]);
	return (minishell);
}

t_shell_s	*get_num_commands(t_shell_s *minishell, char *str)
{
	t_counter	count;
	
	count.i = 0;
	count.trigger = 0;
	count.counter = 0;
	count.trigger2 = 0;
	if (!str)
		return (minishell);
	// printf("token[0] in get num cmds = %s\n", minishell->lexer->tokens[count.i]);
	while (minishell->lexer->tokens[count.i])
	{
		count.trigger = 0;
		count.trigger2 = 0;
		if (ft_strncmp(minishell->lexer->tokens[count.i], "|", 2) == 0 && minishell->lexer->tokens[count.i + 1])
		{
			count.i++;
			count.trigger = 1;
		}
		// printf("count.i = %i\n", count.i);
		if (minishell->lexer->tokens[count.i][0] == '>' || minishell->lexer->tokens[count.i][0] == '<')
		{
			if (minishell->lexer->tokens[count.i + 1])
			{
				count.trigger2 = 1;
				count.i += 2;
			}
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
		if (count.trigger2 == 0)
			count.i++;
		// printf("i in get_num_commands = %i\n", count.i);
	}
	minishell->num_commands = count.counter;
	printf("number of commands = %i\n", minishell->num_commands);
	return (minishell);
}
//  && minishell->lexer->tokens[count.i + 2]