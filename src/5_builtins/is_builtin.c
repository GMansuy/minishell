/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:58:30 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:23:14 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parent_builtin_check(char *cmd, char *second)
{
	if (!cmd)
		return (0);
	if (ft_strncmp("cd", cmd, ft_strlen("cd") + 1) == 0
		|| (ft_strncmp("export", cmd, ft_strlen("export") + 1) == 0
			&& second != NULL)
		|| ft_strncmp("unset", cmd, ft_strlen("unset") + 1) == 0
		|| ft_strncmp("exit", cmd, ft_strlen("exit") + 1) == 0)
		return (1);
	return (0);
}

int	builtin_check(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp("cd", cmd, ft_strlen("cd") + 1) == 0
		|| ft_strncmp("export", cmd, ft_strlen("export") + 1) == 0
		|| ft_strncmp("echo", cmd, ft_strlen("echo") + 1) == 0
		|| ft_strncmp("unset", cmd, ft_strlen("unset") + 1) == 0
		|| ft_strncmp("exit", cmd, ft_strlen("exit") + 1) == 0
		|| ft_strncmp("pwd", cmd, ft_strlen("pwd") + 1) == 0
		|| ft_strncmp("env", cmd, ft_strlen("env") + 1) == 0)
		return (1);
	return (0);
}

int	is_builtin(t_data *data, t_exec *exec, char *cmd)
{
	if (ft_strncmp("echo", cmd, ft_strlen("echo") + 1) == 0)
		return (echo_cmd(exec->cmd_tab));
	if (ft_strncmp("pwd", cmd, ft_strlen("pwd") + 1) == 0)
		return (pwd_cmd(data, exec));
	else if (ft_strncmp("env", cmd, ft_strlen("env") + 1) == 0)
		return (env_cmd(data->mini_env, exec));
	else if (ft_strncmp("cd", cmd, ft_strlen("cd") + 1) == 0)
		return (cd_cmd(data, data->mini_env, exec->cmd_tab));
	else if (ft_strncmp("export", cmd, ft_strlen("export") + 1) == 0)
		return (export_cmd(data->mini_env, exec, data));
	else if (ft_strncmp("unset", cmd, ft_strlen("unset") + 1) == 0)
		return (unset_cmd(data->mini_env, exec));
	else if (ft_strncmp("exit", cmd, ft_strlen("exit") + 1) == 0)
		return (exit_cmd(exec), 1);
	return (0);
}

int	cmds_builtin(t_exec *exec, t_lexer *lex, t_data *data)
{
	while (lex)
	{
		if (lex->type == CMD)
			get_cmd(lex, exec, data);
		lex = lex->next;
	}
	if (!exec->cmd_tab[0])
		return (reset_exec_info(exec), 1);
	if (!parent_builtin_check(exec->cmd_tab[0], exec->cmd_tab[1]))
		return (reset_exec_info(exec), 1);
	return (0);
}

int	init_builtin(t_data *data, t_exec *exec, t_lexer *lex_list)
{
	int	i;
	int	(*f[5])(t_lexer *, t_exec *, t_data *);

	init_cmd(data->exec);
	if (data->exec->nbr_of_pipes != 0 || cmds_builtin(exec, lex_list, data))
		return (0);
	f[INFILE] = &get_in;
	f[HERE_DOC] = &get_in;
	f[OUTFILE] = &get_out;
	f[APPEND] = &get_out;
	while (lex_list)
	{
		i = 0;
		while (i != lex_list->type)
			i++;
		if (i != CMD)
			if (f[i](lex_list, data->exec, data) != 0)
				return (1);
		lex_list = lex_list->next;
	}
	if (!exec->cmd_tab[0])
		return (close_pipes(data), 0);
	data->errcode = is_builtin(data, exec, exec->cmd_tab[0]);
	return (close_pipes(data), 1);
}
