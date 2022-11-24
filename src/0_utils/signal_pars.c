/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:42 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:03:07 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_sigint(int sig)
{
	t_data	*d;

	(void) sig;
	d = get_data();
	ft_printf("\n");
	exit_free(d, 130);
}

void	sig_heredoc(void)
{
	signal(SIGINT, &heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
