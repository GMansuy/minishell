/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:34:57 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:40:46 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_empty(t_data *data)
{
	char	tmp[1000];

	if (getcwd(tmp, 1000) == NULL)
		exit_free(data, errno);
	data->pwd = ft_oldstrdup(tmp);
	data->path = NULL;
	data->errcode = 0;
	data->envp = NULL;
	ft_envadd_back(&data->mini_env, ft_envnew(ft_oldstrdup("PWD"),
			ft_oldstrdup(tmp), ALL), data);
	ft_envadd_back(&data->mini_env, ft_envnew(ft_oldstrdup("SHLVL"),
			ft_oldstrdup("1"), ALL), data);
	ft_envadd_back(&data->mini_env,
		ft_envnew(ft_oldstrdup("?"), ft_oldstrdup("0"), NOP), data);
}

void	error_value(t_data *data, int errcode)
{
	t_env	*tmp;

	tmp = data->mini_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "?", 1) == 0)
		{
			if (tmp->content)
				free(tmp->content);
			tmp->content = ft_olditoa(errcode);
			if (!tmp->content)
				quit_minishell(data);
			break ;
		}
		tmp = tmp->next;
	}
}
