/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:37:49 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/31 16:45:49 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		neg;
	long	value;

	i = 0;
	neg = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg++;
		i++;
	}
	value = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		value += nptr[i] - '0';
		if (nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
			value *= 10;
		i++;
	}
	if (neg % 2 != 0)
		value = -value;
	return (value);
}
