/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:35:50 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/01 21:13:57 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    free_everything(t_shell_s *minishell)
{
    t_counter   count;

    count.i = 0;
    count.j = 0;
    count.k = 0;
    if (minishell->cmd_line != NULL)
        free(minishell->cmd_line);
    if (minishell->commands != NULL)
    {
        while (minishell->commands[count.i])
            free(minishell->commands[count.i++]);
        free(minishell->commands);
    }
    if (minishell->home != NULL)
        free(minishell->home);
    if (minishell->path != NULL)
    {
        while (minishell->path[count.j])
            free(minishell->path[count.j++]);
        free(minishell->path);
    }
    if (minishell->lexer != NULL)
    {
        if (minishell->lexer->tokens != NULL)
        {
            while (minishell->lexer->tokens[count.k])
                free(minishell->lexer->tokens[count.k++]);
            free(minishell->lexer->tokens);
        }
        free(minishell->lexer);
    }
    if (minishell != NULL)
        free(minishell);
}

void    free_2d(char **array)
{
    int i;

    i = 0;
    if (array != NULL)
    {
        while (array[i])
        {
            if (array[i] != NULL)
                free(array[i++]);
        }
        free(array);
    }
    return ;
}