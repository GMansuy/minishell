/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:44:16 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:20:11 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_variable(t_env *mini_env, char *str, t_data *data)
{
	t_export	n;
	int			i;

	n.name = str;
	n.append = 0;
	n.content = NULL;
	n.display = EXP;
	i = 0;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			n.display = ALL;
			n.append = (str[i - 1] == '+');
			n.name = ft_substr(str, 0, i - n.append);
			n.content = ft_substr(str, i + 1, ft_strlen(str) - i);
		}
	}
	if (replace_in_env(mini_env, &n))
		return ;
	ft_envadd_back(&mini_env,
		ft_envnew(ft_oldstrdup(n.name),
			ft_oldstrdup(n.content), n.display), data);
}

int	parse_export(char *str)
{
	int	i;

	if (!(ft_isalpha(str[0])) && str[0] != '_')
		return (1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_'
			&& !(str[i] == '+' && str[i + 1] == '='))
			return (1);
	}
	return (0);
}

int	check_export(t_env *mini_env, char **cmd_tab, t_data *data)
{
	int	i;
	int	error;

	error = 0;
	i = 1;
	while (cmd_tab[i])
	{
		if (parse_export(cmd_tab[i]) == 0)
			export_variable(mini_env, cmd_tab[i], data);
		else
		{
			builtin_msg(IDENT, cmd_tab[i]);
			error = 1;
		}
		i++;
	}
	return (error);
}

int	export_cmd(t_env *mini_env, t_exec *exec, t_data *data)
{
	init_rank(mini_env);
	if (exec->cmd_tab[1] == NULL)
		return (sort_env(mini_env), 0);
	if (ft_strncmp(exec->cmd_tab[1], "-", 1) == 0)
		return (builtin_msg(OPTIO, "export"), 2);
	return (check_export(mini_env, exec->cmd_tab, data));
}
