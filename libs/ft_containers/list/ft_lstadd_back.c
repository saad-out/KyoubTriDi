/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:49:38 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/06 10:39:13 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

static t_lst	*ft_lstlast(t_lst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

bool	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (new == NULL || lst == NULL)
		return (false);
	if (*lst == NULL)
	{
		*lst = new;
		return (true);
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->prev = last;
	return (true);
}
