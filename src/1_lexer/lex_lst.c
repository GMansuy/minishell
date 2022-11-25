/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:59:33 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/25 18:59:36 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lexadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = NULL;
	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = (tmp)->next;
		tmp->next = new;
		tmp->next->prev = tmp;
	}
	else
		*lst = new;
}

t_lexer	*ft_lexnew(char *content)
{
	t_lexer	*new;

	new = magic_malloc(sizeof(t_lexer));
	new->token = content;
	new->meta = NULL;
	new->wasq = NULL;
	new->type = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// void	ft_lexclear(t_lexer **lst, void (*del)(void *))
// {
// 	t_lexer	*tmp;
// 	if (lst)
// 	{
// 		tmp = *lst;
// 		while (tmp)
// 		{
// 			tmp = tmp->next;
// 			del(tmp->token);
// 			del(*lst);
// 			*lst = tmp;
// 		}
// 		free(lst);
// 	}
// }
