/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:33 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:36:22 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	__test_print_env(t_env *mini_env)
{
	while (mini_env->next)
	{
		ft_printf("%s", mini_env->name);
		ft_printf("=");
		ft_printf("%s\n", mini_env->content);
		mini_env = mini_env->next;
	}
	ft_printf("%s", mini_env->name);
	ft_printf("=");
	ft_printf("%s\n", mini_env->content);
}

void	ft_envadd_back(t_env **lst, t_env *new, t_data *data)
{
	t_env	*tmp;

	if (!new)
		env_free(data->mini_env);
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = (tmp)->next;
	tmp->next = new;
}

t_env	*ft_envnew(char *name, char *content, int display)
{
	t_env	*new;

	if (!name)
		return (free(content), NULL);
	new = malloc (sizeof(t_env));
	if (!new)
		return (free(name), free(content), NULL);
	new->content = content;
	new->name = name;
	new->display = display;
	new->rank = 0;
	new->next = NULL;
	return (new);
}

char	*get_var_name(char *envp_line)
{
	int		i;
	char	*name;

	i = 0;
	while (envp_line[i] && envp_line[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (envp_line[i] && envp_line[i] != '=')
	{
		name[i] = envp_line[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

int	get_env(t_data *data, char **envp)
{
	int		i;
	char	tmp[1000];

	data->mini_env = NULL;
	if (!*envp)
		return (env_empty(data), 0);
	i = 0;
	while (envp[i])
	{
		ft_envadd_back(&data->mini_env, ft_envnew(get_var_name(envp[i]),
				ft_oldstrdup(ft_strchr(envp[i], '=') + 1), ALL), data);
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			data->path = ft_oldsplit(envp[i] + 5, ':');
		i++;
	}
	if (getcwd(tmp, 1000) == NULL)
		quit_minishell(data);
	data->pwd = ft_oldstrdup(tmp);
	data->envp = envp;
	data->errcode = 0;
	ft_envadd_back(&data->mini_env,
		ft_envnew(ft_oldstrdup("?"), ft_oldstrdup("0"), NOP), data);
	return (0);
}
