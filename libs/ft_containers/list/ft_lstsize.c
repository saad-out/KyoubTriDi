/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:02:18 by khalid            #+#    #+#             */
/*   Updated: 2024/02/04 13:00:26 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

size_t	ft_lstsize(t_list *lst)
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
