/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 09:54:02 by khalid            #+#    #+#             */
/*   Updated: 2024/07/06 10:39:17 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lstclear(t_lst **lst, void (*del)(void *))
{
	t_lst	*curr;
	t_lst	*head;

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
