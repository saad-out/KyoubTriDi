/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:38:01 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/05 21:56:13 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char	*s;

	s = str;
	if (n != 0)
	{
		while (n-- > 0)
		{
			if (*s++ == (unsigned char)c)
				return ((void *)s - 1);
		}
		return (NULL);
	}
	return (NULL);
}
