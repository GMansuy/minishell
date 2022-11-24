/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:19:27 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 17:55:24 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_n(char *arg)
{
	int	i;

	if (ft_strncmp(arg, "-n", 2) != 0)
		return (0);
	i = 0;
	while (arg[++i])
		if (arg[i] != 'n')
			return (0);
	return (1);
}

int	echo_cmd(char **cmd_tab)
{
	int	i;
	int	n;

	n = 0;
	if (!cmd_tab[1])
		return (write(1, "\n", 1), 0);
	if (check_n(cmd_tab[1]))
		n = 1;
	i = 1 + n;
	while (cmd_tab[i])
	{
		if (!check_n(cmd_tab[i]) || n != 1)
		{
			write (1, cmd_tab[i], ft_strlen(cmd_tab[i]));
			if (cmd_tab[i + 1])
				write (1, " ", 1);
			n = 2 * (n != 0);
		}
		i++;
	}
	write(1, "\n", 1 * (n == 0));
	return (0);
}
