/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flex_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:57:13 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/25 18:57:17 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	id(char c)
{
	int		i;
	char	*set;

	set = "cspdiuxX +#%";
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (i);
		i++;
	}
	return (20);
}

int	form(int fd, va_list ap, int i)
{
	int	(*fct[10])(int fd, va_list, int);

	fct[_c] = pf_putchar;
	fct[_s] = pf_putstr;
	fct[_p] = pf_point;
	fct[_d] = pf_putnbr_dec;
	fct[_i] = pf_putnbr_dec;
	fct[_u] = pf_utoa;
	fct[_x] = pf_putnbr_hex;
	fct[_X] = pf_putnbr_hex;
	fct[_space] = pf_putnbr_dec;
	fct[_plus] = pf_putnbr_dec;
	return (fct[i % 10](fd, ap, i));
}

int	flex_print(int fd, char *color, const char *s, ...)
{
	va_list		ap;
	int			i;
	int			j;

	i = 0;
	j = 0;
	va_start(ap, s);
	write(fd, color, pf_strlen(RED_B));
	while (s[j])
	{
		if (s[j] == '%' && id(s[++j]) < 10)
		{
			i += form(fd, ap, id(s[j]) - 7 * (s[j] == ' ' && s[j + 1] == 's'));
			j += (id(s[j]) == _space || id(s[j]) == _plus);
		}
		else if ((s[j - 1] == '%' && id(s[j]) == _ht)
			&& (id(s[j + 1]) == _x || id(s[j + 1]) == _X))
			i += write (fd, "0", 1) + form(fd, ap, _ht + id(s[j++ + 1]));
		else if (s[j] == '%')
			i += write (fd, &s[j], 1);
		else if (s[j] != '%')
			i += write (fd, &s[j], 1);
		j++;
	}
	return (write(fd, COL, pf_strlen(COL)), va_end(ap), i);
}
