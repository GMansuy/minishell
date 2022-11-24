/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:04:30 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/02 13:54:07 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_lexer
{
	char			*token;
	int				*meta;
	int				*wasq;
	int				type;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

enum	e_quote
{
	NO_QUOTE,
	SINGLE,
	DOUBLE,
};
//-----------------------------------------		lexer
// void	get_token_type(int *heredoc_nb, t_lexer **lex);
// int		get_type(t_lexer *lex_list);
char	*flexdup(char *str, size_t len);
// void	lexer_cut(t_lexer **lex_list, char *str);
//-----------------------------------------		lex_lst
void	ft_lexadd_back(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lexnew(char *content);
void	ft_lexclear(t_lexer **lst, void (*del)(void *));
//-----------------------------------------		lexer_utils
size_t	special_strlen(char *str, char c);
char	*clean_space(char *buf, int *meta);
int		print_tab(char **tab);
int		print_lex(t_lexer **lex);
void	lex_meta(t_lexer *lex, int *meta, int *wasq);

#endif