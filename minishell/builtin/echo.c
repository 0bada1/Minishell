/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:57:45 by szubair           #+#    #+#             */
/*   Updated: 2023/02/10 14:40:32 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_echoflag(char **args, int *i)
{
	char	flag;
	int		j;

	flag = 1;
	*i = 1;
	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		while (args[*i][j] && args[*i][j] == 'n')
			++j;
		if (!args[*i][j] && args[*i][j - 1] == 'n')
			flag = 0;
		else
			break ;
		*i = *i + 1;
	}
	return (flag);
}

int	ft_echo(char **args)
{
	char	flag;
	int		i;

	i = 1;
	flag = ft_echoflag(args, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		++i;
	}
	if (flag)
		ft_putstr_fd("\n", 1);
	free(args);
	return (0);
}