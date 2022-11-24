/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_ux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:43:12 by gmansuy           #+#    #+#             */
/*   Updated: 2022/05/27 15:37:55 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	arg_u(va_list args)
{
	unsigned int	i;
	int				printed_char;

	printed_char = 0;
	i = (unsigned int)va_arg(args, int);
	ft_putnbr((long long)i, &printed_char);
	return (printed_char);
}

int	arg_x(va_list args)
{
	unsigned int	i;
	const char		*hexa = "0123456789abcdef";
	int				printed_char;

	printed_char = 0;
	i = (unsigned int)va_arg(args, int);
	ft_puthexa(i, hexa, &printed_char);
	return (printed_char);
}

int	arg_upperx(va_list args)
{
	unsigned int	i;
	const char		*hexa = "0123456789ABCDEF";
	int				printed_char;

	printed_char = 0;
	i = (unsigned int)va_arg(args, int);
	ft_puthexa(i, hexa, &printed_char);
	return (printed_char);
}

int	arg_double(void)
{
	return (write(1, "%", 1));
}
