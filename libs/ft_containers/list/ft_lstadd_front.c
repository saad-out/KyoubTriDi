/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:35:28 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/06 10:39:15 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

bool	ft_lstadd_front(t_lst **lst, t_lst *new)
{
	if (new == NULL || lst == NULL)
		return (false);
	new->next = *lst;
	if (*lst != NULL)
		(*lst)->prev = new;
	*lst = new;
	return (true);
}
