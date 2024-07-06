/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsearch_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:00:54 by khalid            #+#    #+#             */
/*   Updated: 2024/07/06 10:39:34 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

void	*ft_lstsearh_item(t_lst *lst, void *ref, int (*cmp)())
{
	if (lst == NULL || cmp == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (cmp(ref, lst->content) == 0)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}
