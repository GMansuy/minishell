/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:04:45 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:36:43 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*search_env(t_env *m_env, char *str)
{
	t_env	*tmp;

	tmp = m_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, str, ft_strlen(tmp->name) + 1) == 0)
		{
			return (ft_strdup(tmp->content));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	d_valid(t_lexer *lex, int j)
{
	if (lex->meta[j] != 0 && !lex->token[j + 1])
		return (0);
	if (!(ft_isalnum(lex->token[j + 1]) || lex->token[j + 1] == '_'
			|| lex->token[j + 1] == '?')
		&& (lex->wasq[j + 1] == 0))
		return (0);
	return (lex->token[j] == '$' && lex->meta[j] != 2);
}

int	stop_exp(char *str, int i)
{
	if (ft_isdigit(str[i]) && str[i - 1] == '$')
		return (1);
	if (str[i] == '?' && str[i - 1] == '$')
		return (1);
	return (0);
}
