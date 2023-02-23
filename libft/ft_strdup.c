/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:50:58 by numussan          #+#    #+#             */
/*   Updated: 2022/02/17 03:20:55 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*pointer;
	char	*result;

	if (!s1)
		return (NULL);
	pointer = (char *)s1;
	result = (char *)malloc(ft_strlen(pointer) * sizeof(char) + 1);
	if (!result)
		return (0);
	return (ft_strcpy(result, pointer));
}
