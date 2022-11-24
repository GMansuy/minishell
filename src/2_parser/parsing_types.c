/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:29:28 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 18:16:28 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	infile_parse(t_lexer *lex_list, t_pars *minipars, t_data *data)
{
	int		i;
	char	*token;

	(void) minipars;
	(void) data;
	i = 0;
	token = lex_list->token;
	while (token[i] && (token[i] == '<' || token[i] == ' ' || token[i] == '\t'))
		i++;
	if (!token[i] || token[i] == '>' || token[i] == '|')
		parsing_errors(data, lex_list, 0);
	return (0);
}

int	outfile_parse(t_lexer *lex_list, t_pars *minipars, t_data *data)
{
	int		i;
	char	*token;

	(void) minipars;
	(void) data;
	i = 0;
	token = lex_list->token;
	while (token[i] && (token[i] == '>' || token[i] == ' ' || token[i] == '\t'))
		i++;
	if (!token[i] || token[i] == '<' || token[i] == '|')
		parsing_errors(data, lex_list, 0);
	return (0);
}

int	heredoc_parse(t_lexer *lex_list, t_pars *minipars, t_data *data)
{
	int		i;
	char	*token;

	i = 0;
	token = lex_list->token;
	while (token[i] && (token[i] == '<' || token[i] == ' ' || token[i] == '\t'))
		i++;
	if (!token[i] || token[i] == '>' || token[i] == '|')
		parsing_errors(data, lex_list, 0);
	return (get_heredoc(data, minipars, lex_list));
}

int	append_parse(t_lexer *lex_list, t_pars *minipars, t_data *data)
{
	int		i;
	char	*token;

	(void) minipars;
	(void) data;
	i = 0;
	token = lex_list->token;
	while (token[i] && (token[i] == '>' || token[i] == ' ' || token[i] == '\t'))
		i++;
	if (!token[i] || token[i] == '<' || token[i] == '|')
		parsing_errors(data, lex_list, 0);
	return (0);
}

int	pipe_parse(t_lexer *lex_list, t_pars *minipars, t_data *data)
{
	(void) minipars;
	(void) data;
	if (lex_list->next == NULL || lex_list->next->type == PIPE
		|| !lex_list->prev)
		parsing_errors(data, lex_list, PIPE * (!lex_list->prev));
	return (0);
}
