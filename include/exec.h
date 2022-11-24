/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:34:45 by marvin            #+#    #+#             */
/*   Updated: 2022/10/24 15:42:51 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_export
{
	char	*name;
	char	*content;
	int		display;
	int		append;
}	t_export;

typedef struct s_exec
{
	int		nbr_of_pipes;
	int		nbr_of_cmd;
	int		hd;
	int		*pid;
	int		*pip;
	int		infile;
	int		outfile;
	int		curr_fork;
	char	**cmd_tab;
	int		curr_cmd;
	int		args_nbr;
	int		invalid;
}	t_exec;

#endif
