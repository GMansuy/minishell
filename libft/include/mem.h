/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:28:16 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/19 18:53:51 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H
# include <stdlib.h>

enum {alloc_mem, free_mem, free_one, branch, branch_free};

typedef struct s_mem_stack
{
	void				*ptr;
	struct s_mem_stack	*next;
	struct s_mem_stack	*previous;
	struct s_mem_stack	*parent;
	struct s_mem_stack	*child;
}	t_mem_stack;

void		*magic_malloc(size_t size);
void		mem_stack(void *ptr, int edit);
void		*new(size_t size, size_t count);
t_mem_stack	*create_mem_stack(void *ptr);
void		push_front_mem_stack(t_mem_stack **stack, void *ptr);

void		magic_free(void);
void		free_last(int iter);
void		destroy_stack(t_mem_stack **mem);
void		destroy_one_stack(t_mem_stack **mem);
void		ft_free(void *addr);

t_mem_stack	*new_branch(t_mem_stack **mem, void *ptr);
void		destroy_branch(t_mem_stack **mem);
void		*magic_branch(size_t size);
void		free_branch(void);

#endif
