/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:29:38 by ooutabac          #+#    #+#             */
/*   Updated: 2023/03/05 14:07:34 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int num_of_tokens(char *str)
// {
// 	t_counter   count;

// 	if (!str)
// 		return (0);
// 	count.i = 0;
// 	count.i = skip_spaces(str, 0);
// 	count.counter = 0;
// 	while (str[count.i])
// 	{
// 		if (str[count.i] != ' ' && str[count.i] != '\t')
// 		{
// 			count.i = skip_token(str, count.i);
// 			count.i = skip_spaces(str, count.i);
// 			count.counter++;
// 		}
// 		else
// 			count.i = skip_spaces(str, count.i);
//     }
// 	// printf("No of tokens = %i\n", count.counter);
// 	return (count.counter);
// }

int	num_of_tokens(char *str)
{
	t_counter	count;

	if (!str || !str[0])
		return (0);
	count.i = 0;
	count.counter = 1;
	while (str[count.i])
	{
		while (str[count.i])
		{
			if (str[count.i] == '\"')
			{
				count.i++;
				while (str[count.i] && str[count.i] != '\"')
					count.i++;
				count.i++;
			}
			else if (str[count.i] == '\'')
			{
				count.i++;
				while (str[count.i] && str[count.i] != '\'')
					count.i++;
				count.i++;
			}
			else if (str[count.i] == '>' || str[count.i] == '<' || str[count.i] == '|')
			{
				count.counter++;
				if (count.i > 0 && str[count.i - 1] != ' ' && str[count.i - 1] != '\t')
					count.counter++;
				count.i = skip_symbols(str, count.i);
				count.i = skip_spaces(str, count.i);
			}
			else if (str[count.i] != ' ' && str[count.i] != '\t')
				count.i++;
			else if (str[count.i] == ' ' || str[count.i] == '\t')
			{
				count.counter++;
				count.i = skip_spaces(str, count.i);
			}
		}
	}
	return (count.counter);
}

// int num_of_tokens(char *str)
// {
// 	t_counter   count;

// 	if (!str || !str[0])
// 		return (0);
// 	count.i = skip_spaces(str, 0);
// 	count.counter = 0;
// 	while (str[count.i])
// 	{
// 		while (str[count.i])
// 		{
// 			if (str[count.i] == '\"')
// 			{
// 				count.i++;
// 				while (str[count.i])
// 				{
// 					if (str[count.i] == '\"' && !str[count.i + 1])
// 					{
// 						printf("breaking at str[%i] = %c\n", count.i, str[count.i]);
// 						count.counter++;
// 						return (count.counter);
// 					}
// 					if (str[count.i] == '\"' && (str[count.i + 1] && str[count.i + 1] == ' ' && str[count.i + 1] == '\t'))
// 					{
// 						count.i++;
// 						printf("breaking at str[%i] = %c\n", count.i, str[count.i]);
// 					}
// 					count.i++;
// 				}
// 				count.i++;
// 			}
// 			else if (str[count.i] == '\'')
// 			{
// 				count.i++;
// 				while (str[count.i])
// 				{
// 					if (str[count.i] == '\"' && ((!str[count.i + 1]) || (str[count.i + 1] && str[count.i + 1] == ' ' && str[count.i + 1] == '\t')))
// 						break ;
// 					count.i++;
// 				}
// 				count.i++;
// 			}
// 			else if (str[count.i] != ' ' && str[count.i] != '\t')
// 				count.i++;
// 			else
// 				break ;
// 		}
// 		count.i = skip_spaces(str, count.i);
// 		count.counter++;
// 		// printf("num of tokens in function = %i\n", count.counter);
// 	}
// 	return (count.counter);
// }

char    *get_next_word(char *str, int i)
{
    char    *word;
    int     j;

    if (!str || !str[i])
        return (NULL);
    word = malloc(sizeof(char) * token_size(str, i) + 1);
	// printf("token_size = %i && i = %i\n", token_size(str, i), i);
    i = skip_spaces(str, i);
    j = 0;
    while (str[i] && (str[i] != ' ' && str[i] != '\t'))
    {
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				word[j++] = str[i++];
			}
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
    }
    word[j] = '\0';
    return (word);
}

int token_size(char *str, int i)
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
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				length++;
				i++;
			}
			trigger = 1;
			i++;
		}
		if (length == 0 && ((str[i] == '>' && str[i + 1] && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] && str[i + 1] == '<')))
			return (2);
		else if (length != 0 && ((str[i] == '>' && str[i + 1] && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] && str[i + 1] == '<')))
			return (length);
		if (length == 0 && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
			return (1);
		else if (length != 0 && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
			return (length);
		if (trigger == 0)
		{
        	length++;
        	i++;
		}
    }
	// printf("token size = %i\n", length);
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