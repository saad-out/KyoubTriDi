/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_at_index.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:03:28 by khalid            #+#    #+#             */
/*   Updated: 2024/07/06 10:39:09 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lstadd_at_index(t_lst **lst, t_lst *new, unsigned int index)
{
	t_lst			*head;
	unsigned int	i;

	if (lst == NULL || new == NULL)
		return (false);
	if (index == 0)
		return (ft_lstadd_front(lst, new));
	i = 0;
	head = *lst;
	while (head != NULL)
	{
		if (i == index)
		{
			new->prev = head->prev;
			new->next = head;
			if (head->prev != NULL)
				head->prev->next = new;
			head->prev = new;
			return (true);
		}
		head = head->next;
		i++;
	}
	return (false);
}
