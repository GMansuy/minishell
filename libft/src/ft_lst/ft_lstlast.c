/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:35:25 by gmansuy           #+#    #+#             */
/*   Updated: 2022/05/11 18:46:49 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	size;
	int	node;

	size = ft_lstsize(lst);
	node = 0;
	while (node < size - 1)
	{
		lst = lst->next;
		node ++;
	}
	return (lst);
}
