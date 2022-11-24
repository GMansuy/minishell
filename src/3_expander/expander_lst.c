/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:21:46 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/01 17:41:00 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expadd_back(t_exp **lst, t_exp *new)
{
	t_exp	*tmp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = (tmp)->next;
	tmp->next = new;
}

t_exp	*expnew(void *content, int valid)
{
	t_exp	*new;

	new = magic_malloc (sizeof(t_exp));
	if (!new)
		return (NULL);
	new->content = content;
	new->valid = valid;
	new->was_expanded = 0;
	new->next = NULL;
	return (new);
}
