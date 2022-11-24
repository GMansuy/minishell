/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:31:43 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:42:25 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	d_valid_hd(char *str, int j)
{
	return (ft_isalnum(str[j + 1]) || str[j + 1] == '_'
		|| str[j + 1] == '?');
}

void	cut_expand_hd(char *str, int *i, int *j, t_exp ***lst)
{
	while (str[*i])
	{
		if (!(ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '?'))
		{
			expadd_back(*lst, expnew(ft_substr(str, *j, (*i) - (*j)),
					d_valid_hd(str, *j)));
			(*j) = (*i);
			return ;
		}
		if (stop_exp(str, *i))
		{
			expadd_back(*lst, expnew(ft_substr(str, *j, ((*i) + 1) - (*j)),
					d_valid_hd(str, *j)));
			(*j) = (*i) + 1;
			return ;
		}
		(*i)++;
	}
}

void	split_hd_exp(char *str, t_exp **lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			expadd_back(lst, expnew(ft_substr(str, j, i - j),
					d_valid_hd(str, j)));
			j = i;
			i++;
			cut_expand_hd(str, &i, &j, &lst);
			continue ;
		}
		if (str[i])
			i++;
	}
	if (j + 1 <= i)
		expadd_back(lst, expnew(ft_substr(str, j, i),
				d_valid_hd(str, j)));
}

char	*is_hd_exp(char *str, t_env *env)
{
	t_exp	*lst;
	t_exp	*tmp;
	char	*new;

	lst = NULL;
	new = NULL;
	split_hd_exp(str, &lst);
	tmp = lst;
	while (tmp)
	{
		if (*(char *)(tmp->content) == '$' && tmp->valid == 1)
			tmp->content = search_env(env, tmp->content + 1);
		tmp = tmp->next;
	}
	tmp = lst;
	while (tmp)
	{
		new = ft_strjoin(new, tmp->content);
		tmp = tmp->next;
	}
	return (new);
}

char	*expand_heredoc(char *str, t_data *data, t_lexer *lex)
{
	char	*new;
	int		i;

	i = 1;
	while ((size_t)i < ft_strlen(lex->token) + 1)
	{
		if (lex->wasq[i] != 0)
			return (str);
		i++;
	}
	new = is_hd_exp(str, data->mini_env);
	return (new);
}
