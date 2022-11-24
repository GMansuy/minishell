/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:03:10 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/14 15:32:50 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_line(char *str)
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

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	lst_free(t_lst *lst)
{
	t_lst	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

t_lst	*add_back(t_lst *lst)
{
	t_lst	*tmp;
	int		i;

	if (!(lst))
		return (NULL);
	tmp = malloc(sizeof(t_lst));
	lst->next = tmp;
	tmp->next = NULL;
	i = 0;
	while (i <= BUFFER_SIZE)
		tmp->buf[i++] = 0;
	return (tmp);
}

t_lst	*init_list(void)
{
	t_lst	*lst;

	lst = malloc(sizeof(t_lst));
	if (!lst)
		return (NULL);
	lst->next = NULL;
	lst->buf[0] = 0;
	return (lst);
}
