/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:10:35 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:23:34 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	str_concat(char **str, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		(*str)[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		(*str)[i] = s2[j];
		i++;
		j++;
	}
	(*str)[i] = '\0';
}

char	*join_env(char *s1, char *s2)
{
	size_t	len_1;
	size_t	len_2;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !(*s1))
		return (ft_oldstrdup(s2));
	if (!s2 || !(*s2))
		return (ft_oldstrdup(s1));
	len_1 = 0;
	len_2 = 0;
	while (s1[len_1])
		len_1++;
	while (s2[len_2])
		len_2++;
	str = (char *)malloc (sizeof(char) * (len_1 + len_2 + 1));
	if (!str)
		return (NULL);
	str_concat(&str, s1, s2);
	free(s1);
	return (str);
}

void	init_rank(t_env *mini_env)
{
	while (mini_env)
	{
		mini_env->rank = 0;
		mini_env = mini_env->next;
	}
}

int	replace_in_env(t_env *mini_env, t_export *n)
{
	while (mini_env)
	{
		if ((ft_strncmp(mini_env->name, n->name, ft_strlen(n->name) + 1) == 0))
		{
			if (n->content == NULL)
				return (1);
			if (n->append == 1)
				mini_env->content = join_env(mini_env->content, n->content);
			else
			{
				if (mini_env->content)
					free(mini_env->content);
				mini_env->content = ft_oldstrdup(n->content);
			}
			mini_env->display = n->display;
			return (1);
		}
		mini_env = mini_env->next;
	}
	return (0);
}
