/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:02:44 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:32:29 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	atoi_exit(char *nptr)
{
	int			i;
	int			neg;
	long long	value;

	i = 0;
	neg = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	neg = (nptr[i] == '-');
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	value = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		value += nptr[i] - '0';
		if (nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
			value *= 10;
		i++;
	}
	if ((nptr[i] && (nptr[i] < '0' || nptr[i] > '9')) || value > INT_MAX)
		return (builtin_msg(EXITN, nptr), 2);
	if (neg % 2 != 0)
		value = -value;
	return (value);
}

void	exit_cmd(t_exec *exec)
{
	t_data	*d;
	int		status;

	d = get_data();
	if (exec->cmd_tab[1] && exec->cmd_tab[2])
	{
		if (exec->nbr_of_pipes == 0)
			flex_print(2, YEL_B, "exit\n");
		builtin_msg(TMARG, "exit");
		exit_free(d, 1);
	}
	if (exec->cmd_tab[1])
		status = atoi_exit(exec->cmd_tab[1]);
	else
		status = 0;
	if (exec->nbr_of_pipes == 0)
		flex_print(2, YEL_B, "exit\n");
	exit_free(d, status);
}
