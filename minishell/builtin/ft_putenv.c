/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:16:16 by szubair           #+#    #+#             */
/*   Updated: 2023/02/10 20:38:59 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 

#include "../include/minishell.h"

static char	*get_env_value(const char *string)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	len = ft_strlen(string);
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	while (string[i] != '=')
	{
		value[i] = string[i];
		i++;
	}
		value[i] = '\0';
	return (value);
}

//char	*get_env_string(const char *string, const char *value)
//{
//	int		i;
//	int		value_len;
//	int		string_len;
//	char	*env_string;

//	i = 0;
//	value_len = ft_strlen(value);
//	string_len = ft_strlen(string);
//	env_string = (char *)malloc(sizeof(char) * (string_len + 1));
//	if (!env_string)
//		return (NULL);
//	while (i <= string_len)
//	{
//		env_string[i - value_len - 1] = string[i];
//		i++;
//	}
//	return (env_string);
//}

static int	update_existing_env(const char *string, const char *value)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], value, ft_strlen(value)))
		{
			free(environ[i]);
			environ[i] = ft_strdup(string);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	add_new_env(const char *string)
{
	int		i;
	int		j;
	char	**new_environ;

	i = 0;
	j = 0;
	while (environ[i])
		i++;
	new_environ = (char **)malloc(sizeof(char *) * (i + 2));
	while (j < i)
	{
		new_environ[j] = environ[j];
		j++;
	}
	new_environ[i] = ft_strdup(string);
	new_environ[i + 1] = NULL;
	free(environ);
	environ = new_environ;
}

int	ft_putenv(const char *string)
{
	char *value;
	
	value = get_env_value(string);
	if (!value)
		return (-1);
	if (!update_existing_env(string, value))
		add_new_env(string);
	free(value);
	return (0);
}