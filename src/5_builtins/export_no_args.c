/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:16:30 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/24 15:14:57 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_var(t_env *mini_env)
{
	if (!(mini_env->display == ALL || mini_env->display == EXP)
		|| ft_strncmp("_", mini_env->name, 2) == 0)
		return ;
	if (mini_env->content)
		ft_printf("export %s=%c%s%c\n",
			mini_env->name, '"', mini_env->content, '"');
	else
		ft_printf("export %s\n", mini_env->name);
}

void	print_export(t_env *mini_env)
{
	t_env	*start;
	int		i;
	int		b;

	start = mini_env;
	b = 0;
	i = 1;
	while (b == 0)
	{
		mini_env = start;
		b = 1;
		while (mini_env)
		{
			if (mini_env->rank == i)
			{
				print_var(mini_env);
				b = 0;
			}
			mini_env = mini_env->next;
		}
		i++;
	}
}

int	ranked(t_env *mini_env)
{
	while (mini_env)
	{
		if (mini_env->rank == 0)
			return (0);
		mini_env = mini_env->next;
	}
	return (1);
}

void	find_rank(t_env *mini_env, t_env *start, int i, char **lowest)
{
	while (mini_env)
	{
		if (ft_strncmp(mini_env->name, *lowest, ft_strlen(*lowest)) < 0
			&& mini_env->rank == 0)
			*lowest = mini_env->name;
		mini_env = mini_env->next;
	}
	mini_env = start;
	while (!(ft_strncmp(mini_env->name, *lowest, ft_strlen(*lowest) + 1) == 0))
		mini_env = mini_env->next;
	mini_env->rank = i;
}

void	sort_env(t_env *mini_env)
{
	t_env	*start;
	char	*lowest;
	int		i;

	start = mini_env;
	i = 1;
	lowest = mini_env->name;
	while (!ranked(mini_env))
	{
		while (mini_env->rank != 0)
			mini_env = mini_env->next;
		lowest = mini_env->name;
		mini_env = start;
		find_rank(mini_env, start, i, &lowest);
		i++;
	}
	print_export(start);
}
