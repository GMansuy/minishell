/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:03:48 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:22:49 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_env(t_data *data, t_env *mini_env, char *new_pwd, char *old_pwd)
{
	while (mini_env)
	{
		if (ft_strncmp(mini_env->name, "PWD", 4) == 0)
		{
			free(mini_env->content);
			mini_env->content = ft_oldstrdup(new_pwd);
			if (!mini_env->content)
				quit_minishell(data);
		}
		else if (ft_strncmp(mini_env->name, "OLDPWD", 7) == 0)
		{
			free(mini_env->content);
			mini_env->content = old_pwd;
		}
		mini_env = mini_env->next;
	}	
}

void	new_path(t_data *data, t_env *mini_env)
{
	char	*old_pwd;
	char	new_pwd[1000];

	old_pwd = ft_oldstrdup(data->pwd);
	if (!old_pwd)
		quit_minishell(data);
	if (getcwd(new_pwd, 1000) == NULL)
		quit_minishell(data);
	free(data->pwd);
	data->pwd = ft_oldstrdup(new_pwd);
	if (!data->pwd)
		quit_minishell(data);
	change_env(data, mini_env, new_pwd, old_pwd);
}

int	change_directory(t_data *data, t_env *mini_env, char **cmd_tab)
{
	char	*new;

	if (access(cmd_tab[1], 0) == 0)
	{
		if (chdir(cmd_tab[1]) < 0)
			return (exec_msg(NOTDIR, cmd_tab[1]), 1);
		else
			return (new_path(data, mini_env), 0);
	}
	new = ft_strjoin(data->pwd, "/");
	new = ft_strjoin(new, cmd_tab[1]);
	if (access(new, 0) != 0)
		return (exec_msg(NOFIL, cmd_tab[1]), 1);
	if (chdir(new) < 0)
		return (exec_msg(NOTDIR, cmd_tab[1]), 1);
	return (new_path(data, mini_env), 0);
}

int	user_dir(t_data *data, t_env *mini_env, char **cmd_tab)
{
	t_env	*tmp;
	char	*usrpath;

	tmp = mini_env;
	usrpath = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "HOME", 5) == 0)
			usrpath = tmp->content;
		tmp = tmp->next;
	}
	if (!usrpath)
		return (ft_printf("minishell: HOME not set\n"), 1);
	if (chdir(usrpath) < 0)
		return (exec_msg(NOFIL, cmd_tab[1]), 1);
	return (new_path(data, mini_env), 0);
}

int	cd_cmd(t_data *data, t_env *mini_env, char **cmd_tab)
{
	if (!cmd_tab[1] || ft_strncmp(cmd_tab[1], "~", 2) == 0)
		return (user_dir(data, mini_env, cmd_tab));
	if (cmd_tab[2])
		return (builtin_msg(TMARG, "cd"), 1);
	if (ft_strncmp(cmd_tab[1], "-", 1) == 0)
		return (builtin_msg(OPTIO, "cd"), 2);
	return (change_directory(data, mini_env, cmd_tab));
}
