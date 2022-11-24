/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:51:24 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/31 16:28:34 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing_errors(t_data *data, t_lexer *lex_list, int err_code)
{
	if (err_code == PIPE)
		pars_msg(SYNTX, "|");
	else if (!lex_list->next)
		pars_msg(SYNTX, "newline");
	else
	{
		if (lex_list->next->type == PIPE)
			pars_msg(SYNTX, "|");
		else if (lex_list->next->type == HERE_DOC)
			pars_msg(SYNTX, "<<");
		else if (lex_list->next->type == APPEND)
			pars_msg(SYNTX, ">>");
		else if (lex_list->next->type == INFILE)
			pars_msg(SYNTX, "<");
		else
			pars_msg(SYNTX, ">");
	}
	exit_free(data, 2);
}
