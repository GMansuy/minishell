/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:16:25 by gmansuy           #+#    #+#             */
/*   Updated: 2022/05/06 12:16:26 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp_d;

	i = 0;
	tmp_d = (unsigned char *) s;
	while (i < n)
	{
		tmp_d[i] = c;
		i++;
	}
	return (s);
}
