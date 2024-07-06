/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_at_index.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:34:51 by khalid            #+#    #+#             */
/*   Updated: 2024/07/06 10:39:19 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lstdel_at_index(t_lst **lst, unsigned int index,
		void (*del)(void *))
{
	t_lst			*head;
	unsigned int	i;

	if (lst == NULL || *lst == NULL)
		return (false);
	head = *lst;
	i = 0;
	if (index == 0)
		return (ft_lstdel_front(lst, del));
	while (head != NULL)
	{
		if (i == index)
		{
			head->prev->next = head->next;
			if (head->next != NULL)
				head->next->prev = head->prev;
			del(head->content);
			free(head);
			return (true);
		}
		head = head->next;
		i++;
	}
	return (false);
}
