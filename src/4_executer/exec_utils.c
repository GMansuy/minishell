/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:33:41 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:15:34 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_path(t_env *env)
{
	while (env)
	{
		if (ft_strncmp("PATH", env->name, 5) == 0)
			return (ft_split(env->content, ':'));
		env = env->next;
	}
	return (NULL);
}

int	is_dir(char *str)
{
	DIR	*dirent;

	dirent = opendir(str);
	if (!dirent)
		return (0);
	closedir(dirent);
	return (1);
}

void	error_child(t_data *data, t_exec *exec)
{
	if (data->exec->infile > 0)
		close(data->exec->infile);
	if (data->exec->outfile > 1)
		close(data->exec->outfile);
	if (ft_strncmp("/", exec->cmd_tab[0], 1) == 0
		|| ft_strncmp("./", exec->cmd_tab[0], 2) == 0)
	{
		if (is_dir(exec->cmd_tab[0]))
		{
			exec_msg(ISDIR, exec->cmd_tab[0]);
			exit_free(data, 126);
		}
		exec_msg(NOFIL, exec->cmd_tab[0]);
	}
	else
		exec_msg(NOCMD, exec->cmd_tab[0]);
	close_pipes(data);
	exit_free(data, 127);
}

void	exit_status(t_data *data, int status)
{
	if (status == 139)
	{
		exec_msg(SEGFL, NULL);
		exit_free(data, status);
	}
	else
		exit_free(data, status / 256);
}

void	bash_it(char *cmd, t_data *data, t_exec *exec)
{
	char		*tab[3];
	const char	*bsh = "/usr/bin/bash";

	if (is_dir(exec->cmd_tab[0]))
	{
		exec_msg(ISDIR, exec->cmd_tab[0]);
		exit_free(data, 126);
	}
	tab[0] = ft_strdup("bash");
	tab[1] = ft_strdup(cmd);
	tab[2] = NULL;
	execve(bsh, tab, data->envp);
	error_child(data, exec);
}
