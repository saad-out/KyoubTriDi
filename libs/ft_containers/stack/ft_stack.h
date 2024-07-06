/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:49:09 by khalid            #+#    #+#             */
/*   Updated: 2024/07/06 10:46:11 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H

# include "../list/ft_lst.h"

typedef struct s_struct
{
	t_lst	*top;
	size_t	size;
}			t_stack;

t_stack		*ft_stack_create(void);
bool		ft_stack_is_empty(t_stack *stack);
size_t		ft_stack_size(t_stack *stack);
bool		ft_stack_clear(t_stack *stack, void (*del)(void *));
bool		ft_stack_pop(t_stack *stack, void (*del)(void *));
bool		ft_stack_push(t_stack *stack, void *data);
void		*ft_stack_top(t_stack *stack);

#endif