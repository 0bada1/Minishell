/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 01:05:18 by numussan          #+#    #+#             */
/*   Updated: 2022/02/17 03:21:14 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_checker(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1)
		return (0);
	while (s1[start] && set_checker(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && set_checker(s1[end - 1], set))
		end--;
	return (ft_substr(s1, start, (end - start)));
}
