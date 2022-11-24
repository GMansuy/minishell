/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_gnl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:27:36 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/14 15:43:55 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAGIC_GNL_H
# define MAGIC_GNL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "mem.h"

# define BUFFER_SIZE 1

typedef struct s_mlst	t_mlst;
struct s_mlst
{
	char		buf[BUFFER_SIZE + 1];
	t_mlst		*next;
};

char	*magic_gnl(int fd);
int		mcheck_line(char *str);
int		mlen(char *str);
t_mlst	*madd_back(t_mlst *lst);
t_mlst	*minit_list(void);
void	mlst_free(t_mlst *lst);

#endif
