/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:02:19 by klakbuic          #+#    #+#             */
/*   Updated: 2024/06/29 13:07:49 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#define TRUE 1

int	ft_lst_clear(t_list **lst)
{
	t_list	*pre;
	t_list	*head;

	if ((*lst) == NULL)
		return (1);
	head = *lst;
	while (head != NULL)
	{
		pre = head;
		free(pre->content);
		pre->size = 0;
		head = head->next;
		pre->next = NULL;
		free(pre);
	}
	*lst = NULL;
	return (1);
}

char	*ft_lst_join(t_list *head)
{
	char	*line;
	t_list	*lst;
	size_t	len;
	int		i;

	len = 0;
	lst = head;
	while (lst->next != NULL)
	{
		len += lst->size;
		lst = lst->next;
	}
	len += nl_index(lst->content);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line && ft_lst_clear(&head))
		return (NULL);
	lst = head;
	i = 0;
	while (lst->next != NULL && ft_memcpy((line + i), lst->content, lst->size))
	{
		i += lst->size;
		lst = lst->next;
	}
	ft_memcpy((line + i), lst->content, nl_index(lst->content));
	return (line[len] = '\0', line);
}

void	ft_lst_append(t_list **head, char *buff, size_t nb_read)
{
	t_list	*last;
	t_list	*newnode;

	if (head == NULL || buff == NULL)
		return ;
	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode && ft_lst_clear(head))
		return ;
	newnode->content = buff;
	newnode->size = nb_read;
	newnode->next = NULL;
	if (*head == NULL)
		*head = newnode;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = newnode;
	}
}

char	*make_new_line(t_list **head, int *found)
{
	char	*line;
	char	*carry;
	t_list	*iter;
	int		len;

	if (*head == NULL)
		return (NULL);
	line = ft_lst_join(*head);
	if (!line && ft_lst_clear(head))
		return (NULL);
	iter = *head;
	while (iter->next != NULL)
		iter = iter->next;
	len = ft_strlen((char *)iter->content) - (nl_index(iter->content));
	carry = ft_substr(iter->content, (nl_index(iter->content)), len);
	if (!carry && ft_lst_clear(head))
		return (*found = 0, line);
	ft_lst_clear(head);
	iter = NULL;
	ft_lst_append(head, carry, ft_strlen(carry));
	*found = is_found(carry);
	return (line);
}

char	*get_next_line(int fd)
{
	ssize_t			nb_read;
	char			*buff;
	static t_line	data;

	if (fd < 0)
		return (NULL);
	while (TRUE)
	{
		if (data.found)
			return (make_new_line(&(data.head), &data.found));
		else
		{
			buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
			if (!buff && ft_lst_clear(&(data.head)))
				return (NULL);
			nb_read = read(fd, buff, BUFFER_SIZE);
			if (nb_read == -1)
				return (free(buff), ft_lst_clear(&(data.head)), NULL);
			if (nb_read == 0)
				return (free(buff), make_new_line(&(data.head), &(data.found)));
			buff[nb_read] = '\0';
			ft_lst_append(&(data.head), buff, nb_read);
			data.found = is_found(buff);
		}
	}
}