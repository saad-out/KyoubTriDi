/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:18:28 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/04 13:32:22 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LST_H
# define FT_LST_H

# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

typedef struct s_lst
{
	void			*content;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

t_lst				*ft_lstnew(void *content);
bool				ft_lstadd_front(t_lst **lst, t_lst *new);
bool				ft_lstdel_front(t_lst **lst, void (*del)(void *));
bool				ft_lstadd_back(t_lst **lst, t_lst *new);
bool				ft_lstdel_back(t_lst **lst, void (*del)(void *));
bool				ft_lstclear(t_lst **lst, void (*del)(void *));
void				*ft_lstsearh_item(t_lst *lst, void *ref, int (*cmp)());
size_t				ft_lstsize(t_lst *lst);
void				ft_lstiter(t_lst *lst, void (*f)(void *));
t_lst				*ft_lstmap(t_lst *lst, void *(*f)(void *),
						void (*del)(void *));
bool				ft_lstdel_at_index(t_lst **lst, unsigned int index,
						void (*del)(void *));
bool				ft_lstadd_at_index(t_lst **lst, t_lst *new,
						unsigned int index);

#endif