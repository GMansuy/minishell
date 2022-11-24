/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:31:59 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/31 17:18:14 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_next_node(t_env *mini_env)
{
	t_env	*tmp;

	tmp = mini_env->next;
	mini_env->next = mini_env->next->next;
	free(tmp->content);
	free(tmp->name);
	free(tmp);
}

int	unset_cmd(t_env *mini_env, t_exec *exec)
{
	char	*target;

	if (!exec->cmd_tab[1])
		return (0);
	target = exec->cmd_tab[1];
	if (ft_strncmp(exec->cmd_tab[1], "-", 1) == 0)
		return (builtin_msg(OPTIO, "unset"), 2);
	while (mini_env)
	{
		if (mini_env->next
			&& ft_strncmp(mini_env->next->name, target,
				ft_strlen(target) + 1) == 0
			&& mini_env->next->display != NOP)
			unset_next_node(mini_env);
		mini_env = mini_env->next;
	}
	return (0);
}
