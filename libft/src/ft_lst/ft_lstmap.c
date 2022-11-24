/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:41:07 by gmansuy           #+#    #+#             */
/*   Updated: 2022/05/11 18:44:18 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_node;
	t_list	*new_node;

	new_node = ft_lstnew(f(lst->content));
	if (!new_node)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	first_node = new_node;
	lst = lst->next;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&first_node, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&first_node, new_node);
	}
	return (first_node);
}
