/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:58:49 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/25 18:58:52 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_sep(char *str, int *wasq, int *meta, int i)
{
	if (is_pipe(str[i - 1]) && meta[i - 1] == 0
		&& str[i] != ' ')
		return (1);
	return (is_pipe(str[i]) && !(is_space(str[i - 1])
			&& !meta[i - 1] && !wasq[i]));
}

int	space_sep(char *str, int *meta, int i)
{
	if (is_arrow(str[i - 1]) && meta[i - 1] == 0 && str[i + 1])
		return (0);
	if (is_space(str[i - 1]) && meta[i - 1] == 0)
		return (0);
	return (is_space(str[i]));
}

int	arrow_sep(char *str, int *wasq, int *meta, int i)
{
	if (is_arrow(str[i]) && is_arrow(str[i - 1]) && str[i] != str[i - 1])
		return (1);
	if (is_space(str[i - 1]) && meta[i - 1] == 0 && wasq[i] == 0
		&& !(i > 1 && is_arrow(str[i - 2])))
		return (0);
	if ((str[i] == str[i - 1] && meta[i - 1] == 0)
		&& !(i > 1 && str[i] == str[i - 2] && meta[i - 2] == 0))
		return (0);
	return (is_arrow(str[i]));
}

int	void_sep(char *str, int *wasq, int *meta, int i)
{	
	if (wasq[i - 1] == 1 && str[i - 1] == ' '
		&& meta[i - 1] == 0 && i == 1)
		return (1);
	if (str[i] != ' ' || str[i - 1] != ' ')
		return (0);
	return (wasq[i] == 1 && meta[i] == 0);
}

int	is_separator(char *str, int *wasq, int *meta, int i)
{
	if (!meta)
		return (0);
	if (meta[i] && meta[i] != 0)
		return (0);
	if (pipe_sep(str, wasq, meta, i) || space_sep(str, meta, i)
		|| arrow_sep(str, wasq, meta, i))
		return (1);
	return (0);
}
