/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:22:22 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/31 17:17:38 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_cmd(t_data *data, t_exec *exec)
{
	if (exec->cmd_tab[1] && ft_strncmp(exec->cmd_tab[1], "-", 1) == 0)
		return (builtin_msg(OPTIO, "pwd"), 2);
	ft_printf("%s\n", data->pwd);
	return (0);
}
