/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:03:25 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/08 09:42:54 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*pre;

	if (!lst || !(*lst) || !del)
		return ;
	head = *lst;
	while (head != NULL)
	{
		del(head->content);
		pre = head;
		head = head->next;
		pre->next = NULL;
		free(pre);
	}
	*lst = NULL;
}
