/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:15:23 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:40:11 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_all(t_data *data)
{
	data->lex_list = NULL;
	data->minipars = NULL;
	data->exec = NULL;
	data->meta = NULL;
	data->del_qu = NULL;
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}
