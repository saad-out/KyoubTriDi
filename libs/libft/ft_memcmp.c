/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:24:05 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/08 09:59:26 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*u1;
	const unsigned char	*u2;

	u1 = s1;
	u2 = s2;
	if (n != 0)
	{
		while (n-- > 0 && *u1++ == *u2++)
			if (n == 0)
				return (0);
		return (*(u1 - 1) - *(u2 - 1));
	}
	return (0);
}
