/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:55:18 by marvin            #+#    #+#             */
/*   Updated: 2022/10/24 14:48:50 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipes(t_data *data)
{
	int	i;

	if (data->exec->infile > 0)
		close(data->exec->infile);
	if (data->exec->outfile > 1)
		close(data->exec->outfile);
	i = 0;
	while (i < (data->exec->nbr_of_pipes * 2))
	{
		if (data->exec->pip[i] >= 0)
			close(data->exec->pip[i]);
		i++;
	}
}

int	set_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->exec->nbr_of_pipes)
	{
		if (pipe(data->exec->pip + i * 2) < 0)
		{
			perror("pipe");
			close(data->exec->infile);
			close(data->exec->outfile);
			exit_free(data, errno);
		}
		i++;
	}
	return (0);
}
