/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:02:11 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/25 18:44:24 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lex_print(t_lexer *lex)
{
	int	i;

	while (lex)
	{
		flex_print(2, WHT_I, "%d\n", lex->type);
		flex_print(2, YEL_B, "%s\n", lex->token);
		i = 0;
		while (i < (int)ft_strlen(lex->token))
		{
			flex_print(2, PPL_B, "%d", lex->meta[i]);
			i++;
		}
		i = 0;
		ft_printf("\n");
		while (i < (int)ft_strlen(lex->token) + 1)
		{
			ft_printf("%d", lex->wasq[i]);
			i++;
		}
		ft_printf("\n\n");
		lex = lex->next;
	}
}

void	space_clear(t_lexer *lex)
{
	while (lex)
	{
		erase_space(lex, 0, 0);
		lex = lex->next;
	}
}

int	lexer_cut(t_data *data, t_lexer **lex_list, char *str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[i])
	{
		if (is_separator(str, data->del_qu, data->meta, i)
			|| void_sep(str, data->del_qu, data->meta, i))
		{
			ft_lexadd_back(lex_list, ft_lexnew(ft_substr(str, j, i - j)));
			j = i;
		}
		i++;
	}
	if ((!(isspace(str[i - 1]) && data->meta[i - 1] == 0 && !is_arrow(str[j])))
		|| data->del_qu[i] == 1 || i == 1)
		ft_lexadd_back(lex_list, ft_lexnew(ft_substr(str, j, i - j)));
	return (0);
}

int	lexer(t_data *data, char *command_buf)
{
	*(data->lex_list) = NULL;
	data->heredoc_nb = 0;
	if (ft_strlen(command_buf) == 1)
		ft_lexadd_back(data->lex_list, ft_lexnew(ft_strdup(command_buf)));
	else
		lexer_cut(data, data->lex_list, command_buf);
	lex_meta(*(data->lex_list), data->meta, data->del_qu);
	space_clear(*(data->lex_list));
	get_token_type(&data->heredoc_nb, data->lex_list);
	return (0);
}
