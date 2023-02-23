/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:54:26 by numussan          #+#    #+#             */
/*   Updated: 2022/02/15 15:08:44 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)haystack;
	i = 0;
	if (*needle == '\0')
		return (str);
	while (i < len && haystack[i])
	{
		j = 0;
		while ((i + j) < len && needle[j]
			&& haystack[i + j] == needle[j])
		{
			j++;
			if (needle[j] == '\0')
				return (str + i);
		}
		i++;
	}
	return (0);
}
