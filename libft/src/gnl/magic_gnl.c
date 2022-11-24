/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:29:34 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/02 18:27:07 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "magic_gnl.h"

static void	fill_buf(char *buf, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (buf[i])
		buf[i++] = '\0';
	if (!*str)
		return ;
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	i++;
	j = 0;
	while (str[i])
		buf[j++] = str[i++];
	buf[i] = '\0';
}

static char	*fill_line(t_mlst *lst, int count)
{
	int		i;
	int		j;
	char	*next_line;

	next_line = (char *) magic_malloc (sizeof(char) * (count + 1));
	if (!next_line)
		return (NULL);
	i = 0;
	while (lst)
	{
		j = 0;
		while (lst->buf[j])
			next_line[i++] = lst->buf[j++];
		lst = lst->next;
	}
	next_line[i] = '\0';
	return (next_line);
}

static char	*trim_line(char *next_line)
{
	int		i;

	i = 0;
	while (next_line[i] != '\n' && next_line[i])
		i++;
	if (!next_line[i])
		return (next_line);
	i++;
	while (next_line[i])
		next_line[i++] = '\0';
	return (next_line);
}

static char	*read_line(char *current_buf, t_mlst *lst, int fd)
{
	t_mlst	*node;
	char	*next_line;
	int		count;
	int		ret;
	int		first;

	first = 0;
	count = 0;
	if (!(*current_buf))
		first = 1;
	count = mlen(lst->buf);
	node = lst;
	while (mcheck_line(node->buf) || first)
	{
		node = madd_back(node);
		ret = read(fd, node->buf, BUFFER_SIZE);
		if (ret == 0 && !*(lst->next->buf) && !*current_buf)
			return (NULL);
		count += ret;
		first = 0;
	}
	next_line = fill_line(lst, count);
	fill_buf(current_buf, node->buf);
	return (next_line);
}

char	*magic_gnl(int fd)
{
	static char	current_buf[BUFFER_SIZE + 1];
	t_mlst		*lst;
	char		*next_line;
	int			i;

	lst = minit_list();
	if (*current_buf)
	{
		i = 0;
		while (current_buf[i])
		{
			lst->buf[i] = current_buf[i];
			i++;
		}
		lst->buf[i] = '\0';
	}
	next_line = read_line(current_buf, lst, fd);
	if (!next_line)
	{
		return (NULL);
	}
	next_line = trim_line(next_line);
	return (next_line);
}
