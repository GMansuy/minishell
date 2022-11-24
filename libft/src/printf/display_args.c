/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:04:30 by gmansuy           #+#    #+#             */
/*   Updated: 2022/05/27 15:38:04 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(long long i, int *printed_char)
{
	char	c;

	if (i < 0)
	{
		i = -i;
		*(printed_char) += write(1, "-", 1);
	}
	if (i > 9)
		ft_putnbr(i / 10, printed_char);
	c = (i % 10) + '0';
	*(printed_char) += write(1, &c, 1);
}

void	ft_puthexa(unsigned int nb, const char *hexa, int *printed_char)
{
	unsigned int	i;

	if (nb > 15)
		ft_puthexa(nb / 16, hexa, printed_char);
	i = nb % 16;
	*(printed_char) += write(1, &(hexa[i]), 1);
}

void	ft_putaddr(unsigned long long nb, int *printed_char)
{
	const char	*hexa = "0123456789abcdef";
	int			i;

	if (nb > 15)
		ft_putaddr(nb / 16, printed_char);
	i = nb % 16;
	(*printed_char) += write (1, &(hexa[i]), 1);
}
