/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:33:35 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/07 14:37:52 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*sc;

	if (!dest && !src)
		return (dest);
	dst = dest;
	sc = src;
	if (n > 0)
	{
		if (dst <= sc)
			ft_memcpy(dst, sc, n);
		else
		{
			while (n > 0)
			{
				*(dst + n - 1) = *(sc + n - 1);
				n--;
			}
		}
	}
	return ((void *)dest);
}
