/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:56:01 by klakbuic          #+#    #+#             */
/*   Updated: 2024/02/04 12:59:57 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

static t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

bool	ft_lstdel_back(t_list **lst, void (*del)(void *))
{
	t_list	*last;

	if (del == NULL || (*lst) == NULL || lst == NULL)
		return (false);
	last = ft_lstlast(*lst);
	if (last->prev != NULL)
		last->prev->next = NULL;
	else
		*lst = NULL;
	last->prev = NULL;
	last->next = NULL;
	del(last->content);
	free(last);
	return (true);
}
