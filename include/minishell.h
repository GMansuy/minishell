/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:45:22 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 17:36:15 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "lexer.h"
# include "exec.h"
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>

typedef struct s_env
{
	char			*name;
	char			*content;
	int				display;
	int				rank;
	struct s_env	*next;
}	t_env;

typedef struct s_exp
{
	char			*content;
	int				valid;
	int				was_expanded;
	struct s_exp	*next;
}	t_exp;

typedef struct s_data
{
	int		heredoc_nb;
	t_lexer	**lex_list;	
	t_env	*mini_env;
	char	**path;
	t_pars	*minipars;
	t_exec	*exec;
	char	**envp;
	char	*command_buf;
	int		*meta;
	int		*del_qu;
	int		errcode;
	char	*pwd;
}	t_data;

typedef struct s_help
{
	int		i;
	int		j;
	int		exp;
	t_lexer *lex;
	char	*str;
}	t_help;

enum	e_type
{
	INFILE,
	HERE_DOC,
	OUTFILE,
	APPEND,
	PIPE,
	CMD,
	EMPTY,
};

enum	e_msg
{
	AMBIG,
	NOFIL,
	NOCMD,
	PARSE,
	FORBID,
	NOTDIR,
	ISDIR,
	SYNTX,
	HERED,
	OPTIO,
	TMARG,
	IDENT,
	EXITN,
	SEGFL,
	QUOT,
};

enum	e_display
{
	ALL,
	ENV,
	EXP,
	NOP,
};
// void	lexer_test(t_data *data, char *command_buf, int *meta);

//0_UTILS
//free
void	quit_minishell(t_data *data);
void	env_free(t_env *mini_env);
void	exit_free(t_data *data, int errcode);
void	reset_minishell(t_data *data);
int		free_tab(char **tab);
//msg
void	expand_msg(int error, char *cmd);
void	pars_msg(int error, char *cmd);
void	perror_msg(char *cmd);
void	exec_msg(int error, char *cmd);	
void	builtin_msg(int error, char *cmd);
//signal
void	sig_readl(void);
void	sig_fork(void);
void	fork_sigint(int sig);
void	sig_heredoc(void);
//init
void	init_all(t_data *data);
t_data	*get_data();

//1_LEXER
//lexer
int		lexer(t_data *data, char *command_buf);
//lexer_pars
int		is_separator(char *str, int *wasq, int *meta, int i);
int		void_sep(char *str, int *wasq, int *meta, int i);
//lexer_utils
int		print_data(t_data *data);
void	erase_space(t_lexer *lex, int i, int j);
void	get_token_type(int *heredoc_nb, t_lexer **lex);

//2_PARSER
//pre_parser
int		forbidden_chars(char *command_buf, int *meta);
//pre_parser_utils
void	tab_zero(int *tab, int len);
int		pre_parser(t_data *data, char *command_buf);
//parser
int		parser(t_data *data);
//parsing_types
int		infile_parse(t_lexer *lex_list, t_pars *minipars, t_data *data);
int		outfile_parse(t_lexer *lex_list, t_pars *minipars, t_data *data);
int		heredoc_parse(t_lexer *lex_list, t_pars *minipars, t_data *data);
int		append_parse(t_lexer *lex_list, t_pars *minipars, t_data *data);
int		pipe_parse(t_lexer *lex_list, t_pars *minipars, t_data *data);
//parsing_utils
void	parsing_errors(t_data *data, t_lexer *lex_list, int err_code);
//get_heredoc
int		get_heredoc(t_data *data, t_pars *minipars, t_lexer *lex);

//3_ENV
//get_env
int		get_env(t_data *data, char **envp);
t_env	*ft_envnew(char *name, char *content, int display);
void	ft_envadd_back(t_env **lst, t_env *new, t_data *data);
//add_to_env
void	error_value(t_data *data, int errcode);
void	env_empty(t_data *data);

//expander
void	expander(t_data *data);
char	*is_expanded(t_lexer *lex_list, t_data *data, char *str);
//expander_utils
char	*search_env(t_env *m_env, char *str);
int		d_valid(t_lexer *lex, int j);
int		stop_exp(char *str, int i);
//expander_lst
void	expadd_back(t_exp **lst, t_exp *new);
t_exp	*expnew(void *content, int valid);
//expand_heredoc
char	*expand_heredoc(char *str, t_data *data, t_lexer *lex);
//post_expander
void	lex_expand(t_lexer *tmp, char *token);
t_exp	*put_sep(t_exp *lst);

//4_EXECUTER
//executer
int		executer(t_data *data);
void	init_cmd(t_exec *exec);
//set_exec
int		get_in(t_lexer *lex_list, t_exec *exec, t_data *data);
int		get_out(t_lexer *lex_list, t_exec *exec, t_data *data);
int		get_cmd(t_lexer *lex_list, t_exec *exec, t_data *data);
void	reset_exec_info(t_exec *exec);
//child_exec
int		child_exec(t_exec *exec, t_data *data, int invalid);
void	set_dup(int reading, int writing, t_exec *exec);
//exec_utils
void	error_child(t_data *data, t_exec *exec);
void	bash_it(char *cmd, t_data *data, t_exec *exec);
void	exit_status(t_data *data, int status);
char	**get_path(t_env *env);
//pipes
void	close_pipes(t_data *data);
int		set_pipe(t_data *data);

//5_BUILTINS
int		builtin_check(char *cmd);
int		is_builtin(t_data *data, t_exec *exec, char *cmd);
int		is_parent_builtin(t_data *data, t_exec *exec, char *cmd);
int		init_builtin(t_data *data, t_exec *exec, t_lexer *lex_list);
//exit_cmd
void	exit_cmd(t_exec *exec);
//env_cmd
int		env_cmd(t_env *mini_env, t_exec *exec);
int		unset_cmd(t_env *mini_env, t_exec *exec);
int		pwd_cmd(t_data *data, t_exec *exec);
//export_cmd
int		export_cmd(t_env *mini_env, t_exec *exec, t_data *data);
//export_no_args
void	sort_env(t_env *mini_env);
//export_utils
void	init_rank(t_env *mini_env);
int		replace_in_env(t_env *mini_env, t_export *n);
//echo_cmd
int		echo_cmd(char **cmd_tab);
//cd_cmd
int		cd_cmd(t_data *data, t_env *mini_env, char **cmd_tab);

#endif