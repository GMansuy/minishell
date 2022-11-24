/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:17:53 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:04:48 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_msg(int error, char *cmd)
{
	(void)cmd;
	if (error == AMBIG)
		flex_print(2, COL, "minishell: %s : ambiguous redirect\n", cmd);
}

void	pars_msg(int error, char *cmd)
{
	(void)cmd;
	if (error == FORBID)
		flex_print(2, COL, "minishell: '%s' : forbidden character\n", cmd);
	if (error == HERED)
		flex_print(2, COL,
			"\nminishell: warning: here-document delimited \
by end-of-file (wanted `%s')\n", cmd);
	if (error == SYNTX)
		flex_print(2, COL,
			"minishell: syntax error near unexpected token `%s'\n", cmd);
	if (error == QUOT)
		flex_print(2, COL, "minishell: No matching quote\n");
}

void	perror_msg(char *cmd)
{
	flex_print(2, COL, "minishell: %s", cmd);
	perror(COL);
	ft_printf("%s", COL);
}

void	exec_msg(int error, char *cmd)
{
	if (error == NOTDIR)
		flex_print(2, COL, "minishell: %s: Not a directory\n", cmd);
	if (error == NOFIL)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 29);
	}
	if (error == NOCMD)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Command not found\n", 21);
	}
	if (error == AMBIG)
		flex_print(2, COL,
			"minishell: ambiguous redirect\n");
	if (error == ISDIR)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Is a directory\n", 18);
	}
	if (error == SEGFL)
		flex_print(2, COL, "Segmentation fault (core dumped)\n");
}

void	builtin_msg(int error, char *cmd)
{
	if (error == IDENT)
		flex_print(2, COL,
			"minishell: export: `%s': not a valid identifier\n", cmd);
	if (error == OPTIO)
		flex_print(2, COL, "minishell: %s: invalid option\n", cmd);
	if (error == TMARG)
		flex_print(2, COL, "minishell: %s: too many arguments\n", cmd);
	if (error == EXITN)
		flex_print(2, COL,
			"minishell: exit: %s: numeric argument required\n", cmd);
}
