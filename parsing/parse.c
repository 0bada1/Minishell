/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:29:43 by ooutabac          #+#    #+#             */
/*   Updated: 2023/03/05 14:20:01 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*parse(char *str, char **envp)
{
	t_shell_s	*minishell;

	minishell = ft_calloc(sizeof(t_shell_s), 1);
	minishell->cmd_line = ft_strdup(str);
	minishell = get_path(minishell, envp);
	minishell = get_env_struct(minishell, envp);
	minishell = lexer(minishell, str);
	minishell = raw_lexer(minishell, str);
	if (minishell && minishell->lexer)
		minishell->lexer->command_blocks = split_pipes(str);
	minishell = dollar_sign(minishell);
	if (check_validity(minishell, str) == FALSE)
	{
		free_everything(minishell);
		return (NULL);
	}
	if (minishell)
		minishell->num_pipes = count_pipes(str);
	minishell = get_num_commands(minishell);
	minishell = get_commands(minishell);
	minishell = get_flags(minishell);
	minishell = get_execution_blocks(minishell);
	return (minishell);
}
