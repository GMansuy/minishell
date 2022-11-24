/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouoi <akouoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:29:49 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/16 16:42:28 by akouoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_pars
{
	int	heredoc_nb;
	int	curr_heredoc;
	int	*h_pip;
}	t_pars;

int		open_herepip(t_pars *minipars);
void	close_herepip(t_pars *minipars, int pid);

#endif