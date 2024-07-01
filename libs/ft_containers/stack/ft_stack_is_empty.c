/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_is_empty.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:16:14 by khalid            #+#    #+#             */
/*   Updated: 2024/02/04 12:57:34 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

bool	ft_stack_is_empty(t_stack *stack)
{
	if (stack == NULL)
		return (false);
	return (stack->size == 0);
}
