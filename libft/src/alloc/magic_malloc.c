/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:27:37 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/04 16:10:06 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_mem_stack	*create_mem_stack(void *ptr)
{
	t_mem_stack	*new;

	new = malloc(sizeof(t_mem_stack) * 1);
	if (!new)
	{
		magic_free();
		exit(1);
	}
	new->next = NULL;
	new->previous = NULL;
	new->ptr = ptr;
	new->parent = NULL;
	new->child = NULL;
	return (new);
}

void	push_back_mem_stack(t_mem_stack **stack, void *ptr)
{
	t_mem_stack	*p;
	t_mem_stack	*new;

	p = *stack;
	new = create_mem_stack(ptr);
	while (p->next != NULL)
		p = p->next;
	new->previous = p;
	new->parent = p->parent;
	new->child = p->child;
	p->next = new;
}

void	push_front_mem_stack(t_mem_stack **stack, void *ptr)
{
	t_mem_stack	*p;
	t_mem_stack	*new;

	p = *stack;
	new = create_mem_stack(ptr);
	while (p->previous != NULL)
		p = p->previous;
	new->next = p;
	new->parent = p->parent;
	new->child = p->child;
	p->previous = new;
	*stack = new;
}

void	mem_stack(void *ptr, int edit)
{
	static t_mem_stack	*m_stack = NULL;

	if (ptr != NULL && edit == alloc_mem)
	{
		if (m_stack == NULL)
			m_stack = create_mem_stack(ptr);
		else
			push_front_mem_stack(&m_stack, ptr);
	}
	else if (edit == free_mem)
		destroy_stack(&m_stack);
	else if (edit == free_one)
		destroy_one_stack(&m_stack);
	else if (edit == branch)
		m_stack = new_branch(&m_stack, ptr);
	else if (edit == branch_free)
		destroy_branch(&m_stack);
}

void	*magic_malloc(size_t size)
{
	void	*mem;

	mem = calloc(size, 1);
	if (!mem)
	{
		magic_free();
		exit(1);
	}
	mem_stack(mem, alloc_mem);
	return (mem);
}
