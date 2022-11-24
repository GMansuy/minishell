/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:11 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/09 16:13:40 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnbr(unsigned int nbr, int fd)
{
	char	c;

	if (nbr > 9)
	{
		putnbr(nbr / 10, fd);
	}
	c = (nbr % 10) + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n < 0)
	{
		write(fd, "-", 1);
		nbr = (unsigned int) -n;
	}
	else
		nbr = (unsigned int) n;
	putnbr(nbr, fd);
}
