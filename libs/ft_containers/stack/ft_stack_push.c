/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:53:23 by khalid            #+#    #+#             */
/*   Updated: 2024/02/04 12:58:22 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

bool	ft_stack_push(t_stack *stack, void *data)
{
	bool	feedback;

	if (stack == NULL)
		return (false);
	feedback = ft_lstadd_front(&stack->top, ft_lstnew(data));
	if (feedback == true)
	{
		stack->size++;
		return (true);
	}
	return (false);
}
