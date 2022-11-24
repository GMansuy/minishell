/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flex_print.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouoi <akouoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:52:24 by akouoi            #+#    #+#             */
/*   Updated: 2022/10/16 15:06:31 by akouoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef flex_print_H
# define flex_print_H

# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
//-----------------------------------------		flex_print
int		id(char c);
int		form(int fd, va_list ap, int i);
int		ft_print_fd(int fd, char *color, const char *s, va_list ap);
int		flex_print(int fd, char *color, const char *s, ...);

//-----------------------------------------		ft_str_fd
int		pf_putstr(int fd, va_list ap, int i);
int		pf_putchar(int fd, va_list ap, int i);
//-----------------------------------------		ft_dec_fd
char	*pf_itoa(int fd, int n, char *base);
int		pf_putnbr_dec(int fd, va_list ap, int i);
int		pf_utoa(int fd, va_list ap, int i);
//-----------------------------------------		ft_hex_fd
char	*pf_itoa_base(int fd, unsigned long long int n, char *base);
int		pf_putnbr_hex(int fd, va_list ap, int i);
int		pf_putnbr_hexm(int fd, va_list ap, int i);
int		pf_point(int fd, va_list ap, int i);

size_t	pf_strlen(const char *str);
int		pf_nblen(unsigned long long int n, unsigned long long int base_len);

enum	e_flag
{
	_c,
	_s,
	_p,
	_d,
	_i,
	_u,
	_x,
	_X,
	_space,
	_plus,
	_ht,
	_pct,
};

# define RED_B		"\033[31;01m"
# define RED_S		"\033[31;02m"
# define RED_I		"\033[31;03m"
# define RED_U		"\033[31;04m"

# define GRN_B		"\033[32;01m"
# define GRN_S		"\033[32;02m"
# define GRN_I		"\033[32;03m"
# define GRN_U		"\033[32;04m"

# define YEL_B		"\033[33;01m"
# define YEL_S		"\033[33;02m"
# define YEL_I		"\033[33;03m"
# define YEL_U		"\033[33;04m"

# define ORN_B		"\033[33;01m"
# define ORN_S		"\033[33;02m"
# define ORN_I		"\033[33;03m"
# define ORN_U		"\033[33;04m"

# define PPL_B		"\033[35;01m"
# define PPL_S		"\033[35;02m"
# define PPL_I		"\033[35;03m"
# define PPL_U		"\033[35;04m"

# define BLU_B		"\033[36;01m"
# define BLU_S		"\033[36;02m"
# define BLU_I		"\033[36;03m"
# define BLU_U		"\033[36;04m"

# define WHT		"\033[37;00m"
# define WHT_B		"\033[37;01m"
# define WHT_S		"\033[37;02m"
# define WHT_I		"\033[37;03m"
# define WHT_U		"\033[37;04m"

# define COL		"\033[00m"

#endif
