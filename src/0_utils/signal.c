/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:55:16 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:05:30 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fork_sigint(int sig)
{
	t_data	*d;

	(void) sig;
	d = get_data();
	ft_printf("\n");
	exit_free(d, 130);
}

void	fork_sigquit(int sig)
{
	t_data	*d;

	d = get_data();
	(void) sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
	exit_free(d, 131);
}

void	readl_sigint(int sig)
{
	t_data	*d;

	(void) sig;
	d = get_data();
	d->errcode = 130;
	error_value(d, d->errcode);
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_readl(void)
{
	signal(SIGINT, &readl_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_fork(void)
{
	signal(SIGINT, &fork_sigint);
	signal(SIGQUIT, &fork_sigquit);
}
