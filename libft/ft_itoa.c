/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 00:09:17 by numussan          #+#    #+#             */
/*   Updated: 2022/02/17 03:19:32 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_if_zero(int n, char *str)
{
	if (n == 0)
		str[0] = '0';
	return (str);
}

static int	ft_number_of_string_elements(int n)
{
	int		i;
	int		num;

	i = 0;
	num = n;
	while (num)
	{
		num = num / 10;
		i++;
	}
	i = i + (n <= 0);
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	i = ft_number_of_string_elements(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_if_zero(n, str);
	str[i] = '\0';
	while (n)
	{
		str[--i] = (char)((n % 10) * sign + '0');
		n = n / 10;
	}
	if (sign < 0)
		str[--i] = '-';
	return (str);
}
