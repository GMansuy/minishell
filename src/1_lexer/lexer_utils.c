/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:58:58 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/25 18:59:02 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_type(t_lexer *lex)
{	
	if (ft_strncmp(lex->token, ">>", 2) == 0)
		return (lex->type = APPEND, APPEND);
	else if (ft_strncmp(lex->token, "<<", 2) == 0)
		return (lex->type = HERE_DOC, HERE_DOC);
	else if (ft_strncmp(lex->token, "|", 2) == 0)
		return (lex->type = PIPE, PIPE);
	else if (ft_strncmp(lex->token, ">", 1) == 0)
		return (lex->type = OUTFILE, OUTFILE);
	else if (ft_strncmp(lex->token, "<", 1) == 0)
		return (lex->type = INFILE, INFILE);
	return (lex->type = CMD, CMD);
}

void	get_token_type(int *heredoc_nb, t_lexer **lex)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = *lex;
	while (tmp)
	{
		if (get_type(tmp) == HERE_DOC)
			(*heredoc_nb)++;
		tmp = tmp->next;
		i++;
	}
}

void	erase_space(t_lexer *lex, int i, int j)
{
	char	*new;
	int		*meta;
	int		*wasq;

	new = magic_malloc(sizeof(char) * (ft_strlen(lex->token) + 1));
	meta = magic_malloc(sizeof(int) * (ft_strlen(lex->token)));
	wasq = magic_malloc(sizeof(int) * (ft_strlen(lex->token) + 1));
	i = 0;
	j = 0;
	while (lex->token[i])
	{
		while (lex->token[i] == ' ' && lex->meta[i] == 0)
			i++;
		new[j] = lex->token[i];
		meta[j] = lex->meta[i];
		wasq[j] = lex->wasq[i];
		i++;
		j++;
	}
	new[j] = '\0';
	wasq[j] = lex->wasq[i];
	lex->token = new;
	lex->meta = meta;
	lex->wasq = wasq;
}

int	*ft_subtab(int *tab, unsigned int start, int len)
{
	int		*sub;
	int		i;

	sub = magic_malloc(sizeof(int) * len);
	tab_zero(sub, len);
	i = 0;
	while (i < len)
	{
		sub[i] = tab[start + i];
		i++;
	}
	return (sub);
}

void	lex_meta(t_lexer *lex, int *meta, int *wasq)
{
	int	i;
	int	k;

	k = 0;
	while (lex)
	{
		i = 0;
		while (lex->token[i])
			i++;
		k += i;
		lex->meta = ft_subtab(meta, k - i, i);
		lex->wasq = ft_subtab(wasq, k - i, i + 1);
		lex = lex->next;
	}
}
