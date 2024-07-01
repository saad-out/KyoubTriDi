/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:39:37 by khalid            #+#    #+#             */
/*   Updated: 2024/02/04 12:57:25 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

bool	ft_stack_clear(t_stack *stack, void (*del)(void *))
{
	if (stack == NULL)
		return (false);
	return (ft_lstclear(&stack->top, del));
}
