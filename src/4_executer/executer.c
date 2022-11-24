/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:02:03 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:19:38 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command(t_data *data)
{
	if (!(data->exec->cmd_tab[0]))
		data->exec->invalid = 1;
	child_exec(data->exec, data, data->exec->invalid);
	reset_exec_info(data->exec);
	data->exec->invalid = 0;
	return (0);
}

void	exec_loop(t_lexer *lex_list, t_data *data)
{
	int	i;
	int	(*f[6])(t_lexer *, t_exec *, t_data *);

	f[INFILE] = &get_in;
	f[HERE_DOC] = &get_in;
	f[OUTFILE] = &get_out;
	f[APPEND] = &get_out;
	f[CMD] = &get_cmd;
	data->exec->invalid = 0;
	while (lex_list)
	{
		i = 0;
		while (i != lex_list->type)
			i++;
		if (lex_list->type != PIPE)
		{
			if (!data->exec->invalid && f[i](lex_list, data->exec, data))
				data->exec->invalid = 1;
		}
		else
			execute_command(data);
		lex_list = lex_list->next;
	}
	execute_command(data);
}

void	init_exec(t_lexer *lex_list, t_data *data, t_exec *exec)
{
	if (!exec)
		quit_minishell(data);
	exec->infile = 0;
	exec->outfile = 1;
	exec->nbr_of_pipes = 0;
	exec->nbr_of_cmd = 0;
	exec->curr_fork = 0;
	exec->args_nbr = 0;
	exec->curr_cmd = 0;
	while (lex_list)
	{
		if (lex_list->type == PIPE)
			exec->nbr_of_pipes++;
		if (lex_list->type == CMD)
			exec->nbr_of_cmd++;
		lex_list = lex_list->next;
	}
	exec->hd = 0;
	exec->pid = magic_malloc(sizeof(int) * (exec->nbr_of_pipes + 1));
	exec->pip = magic_malloc(sizeof(int) * (exec->nbr_of_pipes * 2 + 2));
	exec->cmd_tab = magic_malloc(sizeof(char *) * (exec->nbr_of_cmd + 1));
	if (!exec->pid || !exec->pip || !exec->cmd_tab)
		quit_minishell(data);
}

void	init_cmd(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nbr_of_cmd)
	{
		exec->cmd_tab[i] = NULL;
		i++;
	}
	exec->cmd_tab[i] = NULL;
}

int	executer(t_data *data)
{
	int	i;
	int	status;
	int	pid;

	data->exec = magic_malloc(sizeof(t_exec));
	init_exec(*(data->lex_list), data, data->exec);
	if (init_builtin(data, data->exec, *(data->lex_list)) != 0)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		sig_fork();
		status = 0;
		init_cmd(data->exec);
		set_pipe(data);
		exec_loop(*(data->lex_list), data);
		close_pipes(data);
		i = -1;
		while (++i < data->exec->nbr_of_pipes + 1)
			waitpid(data->exec->pid[i], &status, 0);
		exit_status(data, status);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(-1, &status, 0);
	return (data->errcode = status / 256, 0);
}
