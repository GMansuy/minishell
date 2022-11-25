/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:55:31 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/25 15:54:55 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_help	*init_h(t_lexer *lex, char *str)
{
	t_help	*h;

	h = magic_malloc(sizeof(t_help));
	h->exp = 0;
	h->i = 0;
	h->j = 0;
	h->lex = lex;
	h->str = str;
	return (h);
}

void	add_node(t_help *h, int newexp, int option, t_exp **lst)
{
	expadd_back(lst, expnew(ft_substr(h->str, h->j, (h->i + option) - h->j),
			d_valid(h->lex, h->j)));
	h->j = h->i + option;
	h->exp = newexp;
}

void	split_expand(t_lexer *lex_list, char *str, t_exp **lst, t_help *h)
{
	while (str[h->i])
	{
		if (str[h->i] == '$')
			add_node(h, 1, 0, lst);
		else if (h->exp == 1 && (!(ft_isalnum(str[h->i]) || str[h->i] == '_'
					|| str[h->i] == '?') || lex_list->wasq[h->i]))
			add_node(h, 0, 0, lst);
		else if (h->exp == 1 && stop_exp(str, h->i))
			add_node(h, 0, 1, lst);
		h->i ++;
	}
	if (h->j + 1 <= h->i)
		expadd_back(lst, expnew(ft_substr(str, h->j, h->i),
				d_valid(lex_list, h->j)));
}

char	*is_expanded(t_lexer *lex_list, t_data *data, char *str)
{
	t_exp	*lst;
	t_exp	*tmp;
	char	*new;

	lst = NULL;
	new = NULL;
	split_expand(lex_list, str, &lst, init_h(lex_list, str));
	tmp = lst;
	while (tmp)
	{
		if (*(char *)(tmp->content) == '$' && tmp->valid == 1)
		{
			tmp->content = search_env(data->mini_env, tmp->content + 1);
			if (tmp->content)
				tmp->was_expanded = 1;
		}
		tmp = tmp->next;
	}
	tmp = put_sep(lst);
	while (tmp)
	{
		new = ft_strjoin(new, tmp->content);
		tmp = tmp->next;
	}
	return (new);
}

void	expander(t_data *data)
{
	t_lexer	*lex_list;

	lex_list = *data->lex_list;
	while (lex_list)
	{
		lex_list->token = is_expanded(lex_list, data, lex_list->token);
		lex_list = lex_list->next;
	}
	lex_list = *data->lex_list;
	while (lex_list)
	{
		if (lex_list->token)
			lex_expand(lex_list, lex_list->token);
		lex_list = lex_list->next;
	}
}
