/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_gnl_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:03:10 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/02 18:27:25 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "magic_gnl.h"

int	mcheck_line(char *str)
{
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str == '\n' || *str == '\0')
			return (0);
		str++;
	}
	return (1);
}

int	mlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	mlst_free(t_mlst *lst)
{
	t_mlst	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

t_mlst	*madd_back(t_mlst *lst)
{
	t_mlst	*tmp;
	int		i;

	if (!(lst))
		return (NULL);
	tmp = magic_malloc(sizeof(t_mlst));
	lst->next = tmp;
	tmp->next = NULL;
	i = 0;
	while (i <= BUFFER_SIZE)
		tmp->buf[i++] = 0;
	return (tmp);
}

t_mlst	*minit_list(void)
{
	t_mlst	*lst;

	lst = magic_malloc(sizeof(t_mlst));
	if (!lst)
		return (NULL);
	lst->next = NULL;
	lst->buf[0] = 0;
	return (lst);
}
