/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_olditoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:46:37 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/20 10:02:39 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	tab_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len ++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*fill_tab(char *str, unsigned int n, int neg, int *i)
{
	if (neg)
	{
		str[*i] = '-';
		neg = 0;
		(*i)++;
	}
	if (n > 9)
	{
		fill_tab(str, n / 10, neg, i);
		fill_tab(str, n % 10, neg, i);
	}
	else
	{
		str[*i] = n + '0';
		(*i)++;
	}
	return (str);
}

char	*ft_olditoa(int n)
{
	int				len;
	int				i;
	unsigned int	convert;
	char			*str;

	len = tab_len(n);
	str = (char *) malloc (sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
		convert = (unsigned int)(n * -1);
	else
		convert = (unsigned int) n;
	i = 0;
	str = fill_tab(str, convert, n < 0, &i);
	return (str);
}
