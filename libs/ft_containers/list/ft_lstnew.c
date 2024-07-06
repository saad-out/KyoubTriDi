/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:33:29 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/06 10:39:32 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*newnode;

	newnode = (t_lst *)malloc(sizeof(t_lst));
	if (newnode == NULL)
		return (NULL);
	newnode->content = content;
	newnode->prev = NULL;
	newnode->next = NULL;
	return (newnode);
}
