/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:18:28 by klakbuic          #+#    #+#             */
/*   Updated: 2024/02/04 12:25:50 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_H
# define FT_LST_H

# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

t_list				*ft_lstnew(void *content);
bool				ft_lstadd_front(t_list **lst, t_list *new);
bool				ft_lstdel_front(t_list **lst, void (*del)(void *));
bool				ft_lstadd_back(t_list **lst, t_list *new);
bool				ft_lstdel_back(t_list **lst, void (*del)(void *));
bool				ft_lstclear(t_list **lst, void (*del)(void *));
void				*ft_lstsearh_item(t_list *lst, void *ref, int (*cmp)());
size_t				ft_lstsize(t_list *lst);
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
bool				ft_lstdel_at_index(t_list **lst, unsigned int index,
						void (*del)(void *));
bool				ft_lstadd_at_index(t_list **lst, t_list *new,
						unsigned int index);

#endif