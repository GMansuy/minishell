/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:59:02 by marvin            #+#    #+#             */
/*   Updated: 2022/10/24 15:23:40 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	__test_print_exec(t_exec *exec)
{
	int	i;

	i = 0;
	flex_print(2, GRN_B, "EXECUTION %d", exec->curr_fork);
	flex_print(2, WHT_B, " --> ");
	while (i < exec->curr_cmd)
	{
		write(2, exec->cmd_tab[i], ft_strlen(exec->cmd_tab[i]));
		write(2, " ", 1);
		i++;
	}
	flex_print(2, WHT_B, "--> ");
	flex_print(2, RED_B, "INFILE : %d | ", exec->infile);
	flex_print(2, RED_B, "OUTFILE : %d\n\n", exec->outfile);
}

int	check_abs_path(char *cmd, char **paths)
{
	if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, 0) == 0)
			return (2);
		else
			return (0);
	}
	if (!paths)
		return (0);
	return (1);
}

char	*find_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int		signal;

	if (!*cmd)
		return (NULL);
	signal = check_abs_path(cmd, paths);
	if (!signal)
		return (NULL);
	if (signal == 2)
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		if (!command)
			return (NULL);
		if (access(command, 0) == 0)
			return (command);
		paths++;
	}
	return (NULL);
}

void	set_dup(int reading, int writing, t_exec *exec)
{
	if (exec->curr_fork != 0 && exec->infile == 0)
	{
		exec->infile = reading;
	}
	if (exec->curr_fork != exec->nbr_of_pipes && exec->outfile == 1)
	{
		exec->outfile = writing;
	}
	dup2(exec->infile, 0);
	dup2(exec->outfile, 1);
}

int	child_exec(t_exec *exec, t_data *data, int invalid)
{
	char	*cmd;

	exec->pid[exec->curr_fork] = fork();
	if (exec->pid[exec->curr_fork] < 0)
		return (perror("fork"), exit_free(data, errno), 0);
	if (exec->pid[exec->curr_fork] == 0)
	{
		if (invalid)
			exit_free(data, errno);
		set_dup(exec->pip[(2 * exec->curr_fork - 2) * (exec->curr_fork != 0)],
			exec->pip[2 * exec->curr_fork + 1], exec);
		if (builtin_check(exec->cmd_tab[0]) != 0)
		{
			close_pipes(data);
			exit_free(data, is_builtin(data, exec, exec->cmd_tab[0]));
		}
		cmd = find_cmd(get_path(data->mini_env), exec->cmd_tab[0]);
		if (!cmd)
			error_child(data, exec);
		close_pipes(data);
		execve(cmd, exec->cmd_tab, data->envp);
		bash_it(cmd, data, exec);
	}
	return (exec->curr_fork ++, 0);
}
