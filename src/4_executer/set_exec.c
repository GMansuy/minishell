/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:38:18 by marvin            #+#    #+#             */
/*   Updated: 2022/10/24 14:58:25 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_in(t_lexer *lex_list, t_exec *exec, t_data *data)
{
	if (exec->infile > 0)
		close(exec->infile);
	if (lex_list->type == INFILE)
	{
		if (!*(lex_list->token + 1))
			return (exec_msg(AMBIG, NULL), 1);
		exec->infile = open(lex_list->token + 1, O_RDONLY);
		if (exec->infile < 0)
			return (perror_msg(lex_list->token + 1), exec->infile = 0, 1);
	}
	else
	{
		exec->infile = data->minipars->h_pip[2 * exec->hd];
		exec->hd ++;
	}
	return (0);
}

int	get_out(t_lexer *lex_list, t_exec *exec, t_data *data)
{
	(void) data;
	if (exec->outfile > 1)
		close(exec->outfile);
	if (lex_list->type == APPEND)
	{
		if (!*(lex_list->token + 2))
			return (exec_msg(AMBIG, NULL), 1);
		exec->outfile = open(lex_list->token + 2, O_CREAT
				| O_WRONLY | O_APPEND, 0000644);
		if (exec->outfile < 0)
			return (perror_msg(lex_list->token + 2), 1);
	}
	else
	{
		if (!*(lex_list->token + 1))
			return (exec_msg(AMBIG, NULL), 1);
		exec->outfile = open(lex_list->token + 1,
				O_CREAT | O_RDWR | O_TRUNC, 0000644);
		if (exec->outfile < 0)
			return (perror_msg(lex_list->token + 1), 1);
	}
	return (0);
}

int	get_cmd(t_lexer *lex_list, t_exec *exec, t_data *data)
{
	(void) data;
	if (!lex_list->token)
		exec->cmd_tab[exec->curr_cmd] = ft_strdup("");
	else
		exec->cmd_tab[exec->curr_cmd] = ft_strdup(lex_list->token);
	exec->curr_cmd ++;
	return (0);
}

void	reset_exec_info(t_exec *exec)
{
	if (exec->infile > 0)
		close(exec->infile);
	if (exec->outfile > 1)
		close(exec->outfile);
	exec->infile = 0;
	exec->outfile = 1;
	while (exec->curr_cmd > 0)
	{
		exec->cmd_tab[exec->curr_cmd - 1] = NULL;
		exec->curr_cmd --;
	}
}
