/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:16:27 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:41:40 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exp	*put_sep(t_exp *lst)
{
	t_exp	*first;
	int		i;

	first = lst;
	i = 0;
	while (lst)
	{
		while (lst->was_expanded && lst->content[i])
		{
			if (lst->content[i] == ' ')
				lst->content[i] = 4;
			i++;
		}
		i = 0;
		lst = lst->next;
	}
	return (first);
}

t_lexer	*replace_lex(t_lexer *lst, t_lexer *la, t_lexer *lb)
{
	t_lexer	*end;

	if (!*la->token && !*lb->token)
	{
		lst = lst->prev;
		lst->next = lst->next->next;
		return (lst);
	}
	if (!*la->token)
		return (lst->token = lb->token, lst);
	if (!*lb->token)
		return (lst->token = la->token, lst);
	end = lst->next;
	lst->token = la->token;
	lst->next = lb;
	lb->prev = lst;
	lb->next = end;
	if (end)
		end->prev = lb;
	return (lb);
}

void	lex_expand(t_lexer *lst, char *token)
{
	int		i;
	t_lexer	*la;
	t_lexer	*lb;

	i = 0;
	while (token[i])
	{
		if (token[i] == 4)
		{
			la = ft_lexnew(ft_substr(token, 0, i));
			la->type = CMD;
			lb = ft_lexnew(ft_substr(token, i + 1, ft_strlen(token)));
			lb->type = CMD;
			lst = replace_lex(lst, la, lb);
			if (!lst)
				break ;
			token = lst->token;
			i = 0;
			continue ;
		}
		i++;
	}
}
