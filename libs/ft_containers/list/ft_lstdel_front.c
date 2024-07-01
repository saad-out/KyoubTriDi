/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:40:42 by klakbuic          #+#    #+#             */
/*   Updated: 2024/02/04 11:36:29 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lstdel_front(t_list **lst, void (*del)(void *))
{
	t_list	*head;

	if (del == NULL || lst == NULL || *lst == NULL)
		return (false);
	head = *lst;
	if (head->next != NULL)
		*lst = (*lst)->next;
	else
		*lst = NULL;
	del(head->content);
	head->next = NULL;
	head->prev = NULL;
	free(head);
	return (true);
}
