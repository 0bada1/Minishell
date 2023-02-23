/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:07:07 by numussan          #+#    #+#             */
/*   Updated: 2021/12/20 01:02:01 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	count_size;
	void	*pointer;
	void	*pp;

	count_size = count * size;
	pointer = (void *)malloc(count_size);
	if (!pointer)
		return (0);
	pp = pointer;
	while (count_size--)
		*(char *)pp++ = '\0';
	return (pointer);
}
