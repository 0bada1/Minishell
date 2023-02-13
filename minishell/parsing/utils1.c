/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:35:50 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/12 12:42:53 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int	skip_token(char *str, int i)
{
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while (str[i] == '\'' || str[i] == '\"')
				i++;
		}
		else
			i++;
		// printf("str[%i]2 = %c\n", i, str[i]);
	}
	return (i);
}

char	*check_for_input(char *str)
{
	int 	i;
	int		j;
	char	*file_name;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '<')
		{
			i = skip_spaces(str, i + 1);
			file_name = malloc(sizeof(char) * ft_strlen_spaces(str, i) + 1);
			while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '<' && str[i] != '>'))
				file_name[j++] = str[i++];
			file_name[j] = '\0';
			return (file_name);
		}
		i++;
	}
	return (NULL);
}

char	*check_for_output(char *str)
{
	int 	i;
	int		j;
	char	*file_name;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '>')
		{
			i = skip_spaces(str, i + 1);
			file_name = malloc(sizeof(char) * ft_strlen_spaces(str, i) + 1);
			while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '<' && str[i] != '>'))
				file_name[j++] = str[i++];
			file_name[j] = '\0';
			return (file_name);
		}
		i++;
	}
	return (NULL);
}

int	count_pipes(char *str)
{
	t_counter	count;

	count.i = 0;
	count.counter = 0;
	while (str[count.i])
	{
		if (str[count.i] == '|')
			count.counter++;
		count.i++;
	}
	return (count.counter);
}

int	check_pipes_valid(char *str)
{
	t_counter	count;

	count.i = 0;
	count.trigger = 0;
	while (str[count.i] && count.trigger == 0)
	{
		if (str[count.i] == '|')
		{
			count.i = skip_spaces(str, count.i);
			if (str[count.i] == '|' || str[count.i] == '>' || str[count.i] == '<')
				count.trigger = -1;
		}
	}
	return (count.trigger);
}

int	ft_strlen_spaces(char *str, int i)
{
	int	length;

	length = 0;
	while (str[i] && (str[i] != ' ' || str[i] != '\t'))
	{
		length++;
		i++;
	}
	return (length);
}
