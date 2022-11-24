/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:13:34 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:12:44 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_forbidden(char c)
{
	return (c == ';' || c == '(' || c == ')' || c == '&');
}

int	forbidden_chars(char *command_buf, int *meta)
{
	int	i;

	i = 0;
	while (command_buf[i])
	{
		if (is_forbidden(command_buf[i]) && meta[i] == 0)
			return (pars_msg(FORBID, ft_substr(command_buf, i, 1)), 1);
		i++;
	}
	return (0);
}

void	tab_zero(int *tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tab[i] = 0;
		i++;
	}
}
