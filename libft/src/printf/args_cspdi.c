/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_cspdi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:33:31 by gmansuy           #+#    #+#             */
/*   Updated: 2022/05/27 15:37:44 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	arg_c(va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	return (write(1, &c, 1));
}

int	arg_s(va_list args)
{
	char	*str;	
	int		i;

	str = (char *)va_arg(args, char *);
	if (!str)
		return (-2);
	i = 0;
	while (str[i])
		i++;
	return (write(1, str, i));
}

int	arg_p(va_list args)
{
	void					*ptr;
	unsigned long long		convert;
	int						printed_char;

	printed_char = 0;
	ptr = (void *)va_arg(args, void *);
	if (!ptr)
		return (-3);
	convert = (unsigned long long)ptr;
	printed_char += write(1, "0x", 2);
	ft_putaddr(convert, &printed_char);
	return (printed_char);
}

int	arg_d(va_list args)
{
	int	i;
	int	printed_char;

	printed_char = 0;
	i = (int)va_arg(args, int);
	ft_putnbr((long long)i, &printed_char);
	return (printed_char);
}

int	arg_i(va_list args)
{
	int	i;
	int	printed_char;

	printed_char = 0;
	i = (int)va_arg(args, int);
	ft_putnbr((long long)i, &printed_char);
	return (printed_char);
}
