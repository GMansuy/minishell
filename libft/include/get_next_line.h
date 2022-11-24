/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:27:36 by gmansuy           #+#    #+#             */
/*   Updated: 2022/06/24 12:48:56 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 1

typedef struct s_lst	t_lst;
struct s_lst
{
	char		buf[BUFFER_SIZE + 1];
	t_lst		*next;
};

char	*get_next_line(int fd);
int		check_line(char *str);
int		len(char *str);
t_lst	*add_back(t_lst *lst);
t_lst	*init_list(void);
void	lst_free(t_lst *lst);

#endif
