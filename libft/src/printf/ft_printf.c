/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:41:40 by gmansuy           #+#    #+#             */
/*   Updated: 2022/05/27 15:38:12 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	error_case(int buf)
{
	if (buf == -2)
			buf = write(1, "(null)", 6);
	if (buf == -3)
			buf = write(1, "(nil)", 5);
	return (buf);
}

static int	check_str(const char *str, va_list args)
{
	int	i;
	int	buf;
	int	printed_char;

	i = 0;
	printed_char = 0;
	buf = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			buf = read_arg(str, i, args);
			if (buf < 0)
				buf = error_case(buf);
			if (buf != -1)
				i++;
		}
		else
			printed_char += write(1, str + i, 1);
		if (buf >= 0)
			printed_char += buf;
		buf = 0;
		i++;
	}
	return (printed_char);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		printed_char;

	va_start(args, str);
	printed_char = check_str(str, args);
	va_end(args);
	return (printed_char);
}
