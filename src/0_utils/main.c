/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:14:52 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:03:43 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	input_invalid(char *command_buf)
{
	if (!*command_buf)
		return (1);
	if ((*command_buf == '!' || *command_buf == ':' || *command_buf == '#')
		&& ft_strlen(command_buf) == 1)
		return (1);
	while (*command_buf)
	{
		if (*command_buf != ' ' && *command_buf != 9)
			return (0);
		command_buf++;
	}
	return (1);
}

char	*read_input(t_data *data)
{
	char	*command_buf;

	sig_readl();
	while (1)
	{
		command_buf = readline("minishell$> ");
		if (command_buf == NULL)
		{
			flex_print(2, YEL_B, "exit\n");
			quit_minishell(data);
		}
		if (input_invalid(command_buf) == 0)
			add_history(command_buf);
		else
			continue ;
		return (command_buf);
	}
}

int	main_loop(t_data *data)
{
	char	*command_buf;

	while (1)
	{
		init_all(data);
		error_value(data, data->errcode);
		command_buf = read_input(data);
		data->lex_list = magic_malloc(sizeof(t_lexer *));
		if (pre_parser(data, command_buf) != 0)
		{
			reset_minishell(data);
			continue ;
		}
		lexer(data, data->command_buf);
		if (parser(data) != 0)
		{
			reset_minishell(data);
			continue ;
		}
		expander(data);
		executer(data);
		reset_minishell(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1)
		return (flex_print(2, RED_B,
				"minishell: %s: Invalid argument\n", argv[1]), 1);
	data = get_data();
	get_env(data, envp);
	main_loop(data);
	return (0);
}
		//
		// t_lexer *lex = *(data.lex_list);
		// while (lex)
		// {
		// 	flex_print(2, GRN_I, "%s\n", lex->token);
		// 	lex = lex->next;
		// }
		//
