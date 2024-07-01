/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 09:54:02 by khalid            #+#    #+#             */
/*   Updated: 2024/02/04 10:31:06 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*head;

	if (del == NULL || lst == NULL || *lst == NULL)
		return (false);
	head = *lst;
	curr = head;
	while (head != NULL)
	{
		head = head->next;
		del(curr->content);
		curr->next = NULL;
		curr->prev = NULL;
		free(curr);
		curr = head;
	}
	*lst = NULL;
	return (true);
}
