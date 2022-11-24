/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:45:22 by gmansuy           #+#    #+#             */
/*   Updated: 2022/06/24 15:10:33 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

int		read_arg(const char *str, int i, va_list args);
int		arg_c(va_list args);
int		arg_s(va_list args);
int		arg_d(va_list args);
int		arg_p(va_list args);
int		arg_i(va_list args);
int		arg_u(va_list args);
int		arg_x(va_list args);
int		arg_upperx(va_list args);
int		arg_double(void);
void	ft_putstr(char *str);
void	ft_puthexa(unsigned int nb, const char *hexa, int *printed_char);
void	ft_putnbr(long long i, int *printed_char);
void	ft_putaddr(unsigned long long nb, int *printed_char);
int		ft_printf(const char *str, ...);

#endif
