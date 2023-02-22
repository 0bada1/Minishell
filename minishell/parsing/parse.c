/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:29:43 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/22 20:53:11 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*parse(char *str, char **envp)
{
	t_shell_s	*minishell;
	char		*str1;
	char		*str2;

	minishell = ft_calloc(sizeof(t_shell_s), 1);
	str1 = check_for_input(str);
	str2 = check_for_output(str);
	if (str1 != NULL)
	{
		minishell->infile = open(str2, F_OK | X_OK | O_RDONLY, 0777);
		free(str1);
	}
	if (str2 != NULL)
	{
		minishell->outfile = open(str1, F_OK | X_OK | O_RDWR | O_TRUNC, 0777);
		free(str2);
	}
	minishell->cmd_line = ft_strdup(str);
	// printf("count_pipes = %i\n", count_pipes(str));
	// minishell = get_command_blocks(minishell, str);
	minishell = get_path(minishell, envp);
	minishell = get_home(minishell, envp);
	minishell = get_env_struct(minishell, envp);
	minishell = lexer(minishell, str);
	minishell->lexer->command_blocks = split_pipes(str);
	// minishell = raw_lexer(minishell, str);
	if (check_validity(minishell, str) == FALSE)
	{
		free_everything(minishell);
		printf("Error: Syntax\n");
		return (NULL);
	}
	minishell = get_commands(minishell, str);
	return (minishell);
}

// int	check_pipes_valid()
