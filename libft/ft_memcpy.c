/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:21:43 by numussan          #+#    #+#             */
/*   Updated: 2022/02/17 03:14:20 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*temp_dst;
	char	*temp_src;

	if (!dst && !src)
		return (NULL);
	temp_dst = (char *)dst;
	temp_src = (char *)src;
	while (n--)
		*temp_dst++ = *temp_src++;
	return ((void *)dst);
}
