/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:48:06 by gmansuy           #+#    #+#             */
/*   Updated: 2022/05/27 15:38:20 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_arg(const char *str, int i)
{
	const char	*arg_list = "cspdiuxX%";
	int			j;

	j = 0;
	if (!str[i + 1])
		return (0);
	while (arg_list[j])
	{
		if (str[i + 1] == arg_list[j])
			return (1);
		j++;
	}
	return (0);
}

int	read_arg(const char *str, int i, va_list args)
{
	if (!str[i + 1])
		return (-1);
	if (!is_arg(str, i))
		return (-1);
	if (str[i + 1] == 'c')
		return (arg_c(args));
	if (str[i + 1] == 's')
		return (arg_s(args));
	if (str[i + 1] == 'p')
		return (arg_p(args));
	if (str[i + 1] == 'd')
		return (arg_d(args));
	if (str[i + 1] == 'i')
		return (arg_i(args));
	if (str[i + 1] == 'u')
		return (arg_u(args));
	if (str[i + 1] == 'x')
		return (arg_x(args));
	if (str[i + 1] == 'X')
		return (arg_upperx(args));
	if (str[i + 1] == '%')
		return (arg_double());
	return (0);
}
