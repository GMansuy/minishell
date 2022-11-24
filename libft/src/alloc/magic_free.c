/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:37:30 by gmansuy           #+#    #+#             */
/*   Updated: 2022/10/18 14:31:40 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	destroy_one_stack(t_mem_stack **mem)
{
	t_mem_stack	*tmp;

	if ((*mem) != NULL)
	{
		if ((*mem)->ptr != NULL)
			free((*mem)->ptr);
		tmp = *mem;
		if ((*mem)->next)
		{
			*mem = (*mem)->next;
			(*mem)->previous = NULL;
		}
		else
			*mem = NULL;
		free(tmp);
	}
}

void	destroy_stack(t_mem_stack **mem)
{
	t_mem_stack	*tmp;

	while ((*mem) != NULL)
	{
		if ((*mem)->ptr != NULL)
			free((*mem)->ptr);
		tmp = *mem;
		*mem = (*mem)->next;
		free(tmp);
	}
	*mem = NULL;
}

void	magic_free(void)
{
	mem_stack(NULL, free_mem);
}

void	free_last(int iter)
{
	while (iter--)
		mem_stack(NULL, free_one);
}
