/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:27:14 by numussan          #+#    #+#             */
/*   Updated: 2022/02/17 03:14:24 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*temp_src;
	unsigned char		*temp_dst;

	if (!dst && !src)
		return (NULL);
	temp_src = src;
	temp_dst = dst;
	if (dst < src)
	{
		while (len--)
			*temp_dst++ = *temp_src++;
	}
	else
	{
		while (len--)
			*(temp_dst + len) = *(temp_src + len);
	}
	return (dst);
}
