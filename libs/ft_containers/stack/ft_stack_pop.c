/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:58:17 by khalid            #+#    #+#             */
/*   Updated: 2024/02/04 12:58:18 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

bool	ft_stack_pop(t_stack *stack, void (*del)(void *))
{
	bool	feedback;

	if (stack == NULL || ft_stack_is_empty(stack))
		return (false);
	feedback = ft_lstdel_front(&stack->top, del);
	if (feedback == true)
	{
		stack->size--;
		return (true);
	}
	return (false);
}
