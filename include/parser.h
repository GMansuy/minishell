/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:56:18 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/25 18:56:22 by gmansuy          ###   ########.fr       */
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