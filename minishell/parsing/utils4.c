/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:29:38 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/12 19:20:40 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int num_of_tokens(char *str)
{
	t_counter   count;

	count.i = 0;
	count.i = skip_spaces(str, 0);
	count.counter = 0;
	while (str[count.i])
	{
		if (str[count.i] != ' ' && str[count.i] != '\t')
		{
			count.i = skip_token(str, count.i);
			count.counter++;
		}
		count.i = skip_spaces(str, count.i);
    }
	// printf("No of tokens = %i\n", count.counter);
	return (count.counter);
}

char    *get_next_word(char *str, int i)
{
    char    *word;
    int     j;

    if (!str || !str[i])
        return (NULL);
    word = malloc(sizeof(char) * ft_strlen_of_token(str, i) + 1);
	// printf("token_size = %i && i = %i\n", ft_strlen_of_token(str, i), i);
    i = skip_spaces(str, i);
    j = 0;
    while (str[i] && (str[i] != ' ' && str[i] != '\t'))
    {
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				word[j++] = str[i++];
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				word[j++] = str[i++];
			i++;
		}
		else
        	word[j++] = str[i++];
		// printf("%c", str[i]);
    }
	// printf("\n");
    word[j] = '\0';
    return (word);
}

int ft_strlen_of_token(char *str, int i)
{
    int length;
	int	trigger;

    if (!str)
        return (0);
    length = 0;
    i = skip_spaces(str, i);
    while (str[i] && (str[i] != ' ' && str[i] != '\t'))
    { 
		trigger = 0;
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				length++;
				i++;
			}
			trigger = 1;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				length++;
				i++;
			}
			trigger = 1;
		}
		if (trigger == 0)
		{
        	length++;
        	i++;
		}
    }
    return (length);
}

int check_for_dquotes(char *str, int i)
{
    if (!str)
        return (FALSE);
    while (str[i] && (str[i] != ' ' && str[i] != '\t'))
    {
        if (str[i] == '\"')
            return (TRUE);
        i++;
    }
    return (FALSE);
}

// FIX THIS
// int	count_arguments(t_shell_s *minishell, char **command)
// {
// 	t_counter	count;

// 	if (!command)
// 		return (0);
// 	count.i = 0;
// 	count.counter = 0;
// 	while (ft_strncmp(command[count.i], "|", 2) != 0)
// 	{
// 		if (ft_strncmp(command[count.i], ">", 2) == 0 || ft_strncmp(command[count.i], "<", 2) == 0)
// 			count.i += 2;
// 		else
// 			count.i++;
// 		count.counter++;
// 	}
// 	return (count.counter);
// }

// int check_bash_symbols(char *str)
// {
//     t_counter   count;

//     count.i = 0;
//     while (str[count.i])
//     {
//         if (str[count.i] == '>' || str[count.i] == '<' || str[count.i] == )
//     }
// }