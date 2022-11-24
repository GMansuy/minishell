/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:31:59 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/31 17:11:24 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_cmd(t_env *mini_env, t_exec *exec)
{
	if (exec->cmd_tab[1] != NULL)
		return (builtin_msg(TMARG, "env"), 1);
	while (mini_env)
	{
		if (mini_env->display == ALL || mini_env->display == ENV)
			ft_printf("%s=%s\n", mini_env->name, mini_env->content);
		mini_env = mini_env->next;
	}
	return (0);
}
