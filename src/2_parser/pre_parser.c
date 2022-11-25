/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:04:53 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/25 18:43:55 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	preparsing_tester(char *cmd_buf, int *meta, int *del_qu)
{
	int	x;

	x = -1;
	flex_print(2, RED_I, "%s\n", cmd_buf);
	while (++x < (int)ft_strlen(cmd_buf))
		flex_print(2, RED_I, "%d", meta[x]);
	ft_printf("\n");
	x = -1;
	while (++x < (int)ft_strlen(cmd_buf) + 1)
		flex_print(2, RED_I, "%d", del_qu[x]);
	ft_printf("\n");
}

int	matching_quotes(char *command_buf, int *counter)
{
	int	i;
	int	quot;

	quot = 0;
	i = 0;
	while (command_buf[i])
	{
		if ((command_buf[i] == 34 || command_buf[i] == 39) && quot == 0)
		{
			*counter += 2;
			quot = command_buf[i];
			i++;
		}
		if (command_buf[i] == quot)
			quot = 0;
		if (command_buf[i])
			i++;
	}
	return (quot);
}

int	verif_quotes(char *command_buf, int *i, int *quot, int *del_qu)
{
	if ((command_buf[*i] == 34 || command_buf[*i] == 39) && *quot == 0)
	{
		*quot = command_buf[*i];
		*del_qu = 1;
		(*i)++;
	}
	if (command_buf[*i] == *quot)
	{
		*quot = 0;
		*del_qu = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

void	get_meta(t_data *data, char *command_buf)
{
	int	i;
	int	j;
	int	quot;

	quot = 0;
	i = 0;
	j = 0;
	while (command_buf[i])
	{
		if (verif_quotes(command_buf, &i, &quot, data->del_qu + j))
			continue ;
		data->command_buf[j] = command_buf[i];
		data->meta[j] = 1 * (quot != 0) + (quot == 39);
		j++;
		i++;
	}
}

int	pre_parser(t_data *data, char *command_buf)
{
	int	quot;
	int	counter;
	int	len;

	counter = 0;
	quot = matching_quotes(command_buf, &counter);
	if (quot != 0)
		return (pars_msg(QUOT, NULL), 1);
	len = ft_strlen(command_buf);
	data->command_buf = magic_malloc(sizeof(char) * (len + 1));
	data->meta = magic_malloc(sizeof(int) * (len + 1) - counter);
	data->del_qu = magic_malloc(sizeof(int) * (len + 1) - counter);
	if (!data->command_buf || !data->meta || !data->del_qu)
		quit_minishell(data);
	ft_bzero(data->command_buf, len + 1);
	tab_zero(data->meta, len - counter);
	tab_zero(data->del_qu, len + 1 - counter);
	get_meta(data, command_buf);
	if (!*data->command_buf)
		return (ft_putstr_fd("minishell: '': Command not found\n", 2), 1);
	return (forbidden_chars(data->command_buf, data->meta));
}
