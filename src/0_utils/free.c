/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:12:19 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 15:44:00 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

void	reset_minishell(t_data *data)
{
	if (data->minipars)
		close_herepip(data->minipars, 0);
	if (data->exec)
	{
		if (data->exec->infile > 0)
			close(data->exec->infile);
		if (data->exec->outfile > 1)
			close(data->exec->outfile);
	}
	magic_free();
}

void	exit_free(t_data *data, int errcode)
{
	if (data->minipars)
		close_herepip(data->minipars, 0);
	if (data->exec)
	{
		if (data->exec->infile > 0)
			close(data->exec->infile);
		if (data->exec->outfile > 1)
			close(data->exec->outfile);
	}
	if (data->path)
		free_tab(data->path);
	magic_free();
	if (data != NULL)
	{
		free(data->pwd);
		env_free(data->mini_env);
	}
	exit(errcode);
}

void	quit_minishell(t_data *data)
{
	magic_free();
	if (data != NULL)
	{
		free(data->pwd);
		env_free(data->mini_env);
	}
	if (data->path)
		free_tab(data->path);
	exit(2);
}

void	env_free(t_env *mini_env)
{
	t_env	*tmp;

	while (mini_env)
	{
		tmp = mini_env;
		if (mini_env->name)
			free(mini_env->name);
		if (mini_env->content)
			free(mini_env->content);
		mini_env = mini_env->next;
		free(tmp);
	}
}
