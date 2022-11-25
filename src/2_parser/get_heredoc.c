/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:30:09 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/25 15:53:06 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_herepip(t_pars *minipars, int pid)
{
	int	i;

	i = 0;
	if (pid == 0)
	{
		while (i < minipars->heredoc_nb * 2)
		{
			if (minipars->h_pip[i] >= 0)
				close(minipars->h_pip[i]);
			i++;
		}
	}
	else
	{
		while (i < minipars->heredoc_nb)
		{
			close(minipars->h_pip[2 * i + 1]);
			i++;
		}		
	}
}

int	open_herepip(t_pars *minipars)
{
	int	i;

	i = 0;
	while (i < minipars->heredoc_nb)
	{
		if (pipe(minipars->h_pip + 2 * i) < 0)
		{
			perror("pipe");
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_limiter(char *token)
{
	int	i;

	i = 0;
	while (token[i] == '<' || token[i] == ' ')
		i++;
	return (token + i);
}

int	read_heredoc(t_data *data, t_pars *minipars, char *limiter, t_lexer *lex)
{
	char	*buf;

	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = magic_gnl(0);
		if (!buf)
			return (pars_msg(HERED, limiter), 0);
		else if ((!ft_strncmp(limiter, buf, ft_strlen(limiter))
				&& buf[ft_strlen(limiter)] == '\n'))
			return (0);
		buf = expand_heredoc(buf, data, lex);
		write(minipars->h_pip[minipars->curr_heredoc * 2 + 1],
			buf, ft_strlen(buf));
		buf = NULL;
	}
	return (0);
}

int	get_heredoc(t_data *data, t_pars *minipars, t_lexer *lex)
{
	char	*limiter;
	int		pid;
	int		sig;

	sig = 0;
	pid = fork();
	if (pid == 0)
	{
		sig_heredoc();
		limiter = get_limiter(lex->token);
		if (read_heredoc(data, minipars, limiter, lex) != 0)
			exit_free(data, 1);
		close_herepip(minipars, 0);
		exit_free(data, 0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(-1, &sig, 0);
	if (sig == 130 * 256)
		exit_free(data, 130);
	minipars->curr_heredoc ++;
	return (sig);
}
