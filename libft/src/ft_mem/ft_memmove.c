/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:30:31 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/09 16:13:27 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp_d;
	char	*tmp_s;
	size_t	i;

	tmp_s = (char *) src;
	tmp_d = (char *) dest;
	i = n;
	if (tmp_d < tmp_s)
	{
		while (i--)
			*tmp_d++ = *tmp_s++;
	}
	else
	{
		while (i--)
		{
			*(tmp_d + i) = *(tmp_s + i);
		}
	}
	return (dest);
}
