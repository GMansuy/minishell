/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:00:49 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/25 15:43:02 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parsing_loop(t_data *data, t_lexer *lex_list)
{
	int	i;
	int	sig;
	int	(*f[5])(t_lexer *, t_pars *, t_data *);

	f[INFILE] = &infile_parse;
	f[OUTFILE] = &outfile_parse;
	f[HERE_DOC] = &heredoc_parse;
	f[APPEND] = &append_parse;
	f[PIPE] = &pipe_parse;
	sig = 0;
	while (lex_list)
	{
		if (lex_list->type != CMD)
		{
			i = 0;
			while (i != lex_list->type)
				i++;
			sig = f[i](lex_list, data->minipars, data);
		}
		lex_list = lex_list->next;
	}
	return (sig);
}

int	init_parser(t_data *data, t_pars *minipars)
{
	minipars->h_pip = magic_malloc(sizeof(int) * minipars->heredoc_nb * 2);
	if (!minipars->h_pip)
		quit_minishell(data);
	minipars->curr_heredoc = 0;
	if (open_herepip(minipars) != 0)
		return (1);
	return (0);
}

int	parser_fork(t_data *data, t_pars *minipars, t_lexer *lex_list)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		status = parsing_loop(data, lex_list);
		signal(SIGINT, &fork_sigint);
		sig_readl();
		close_herepip(minipars, 0);
		exit_free(data, status / 256);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(-1, &status, 0);
	data->errcode = status / 256;
	close_herepip(minipars, pid);
	return (data->errcode);
}

int	parser(t_data *data)
{
	data->minipars = magic_malloc(sizeof(t_pars));
	if (!data->minipars)
		quit_minishell(data);
	data->minipars->heredoc_nb = data->heredoc_nb;
	if (init_parser(data, data->minipars) != 0)
		return (1);
	return (parser_fork(data, data->minipars, *(data->lex_list)));
}
