/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:02:18 by khalid            #+#    #+#             */
/*   Updated: 2024/07/06 10:39:37 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

size_t	ft_lstsize(t_lst *lst)
{
	size_t	size;

	size = 0;
	if (lst == NULL)
		return (size);
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
