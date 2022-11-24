/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_branch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:59:18 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/19 18:47:42 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_mem_stack *new_branch(t_mem_stack **mem, void *ptr)
{
	t_mem_stack	*new;
	
	new = create_mem_stack(ptr);
	(*mem)->child = new;
	new->parent = *mem;
	return (new);
}

void	destroy_branch(t_mem_stack **mem)
{
	t_mem_stack	*tmp;
	t_mem_stack	*parent;
	
	parent = (*mem)->parent;
	while ((*mem) != NULL)
	{
		if ((*mem)->ptr != NULL)
			free((*mem)->ptr);
		tmp = *mem;
		*mem = (*mem)->next;
		free(tmp);
	}
	*mem = parent;
}

void	*magic_branch(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
	{
		magic_free();
		exit(1);
	}
	mem_stack(mem, branch);
	return (mem);
}

void	free_branch(void)
{
	mem_stack(NULL, branch_free);
}