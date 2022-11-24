/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:36:10 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/09 16:29:01 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_d;
	unsigned char	*tmp_s;

	if (n == 0)
		return (dest);
	i = 0;
	tmp_d = (unsigned char *) dest;
	tmp_s = (unsigned char *) src;
	while (i < n)
	{
		tmp_d[i] = tmp_s[i];
		i++;
	}
	return (dest);
}
