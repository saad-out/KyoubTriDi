/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:11:08 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/07 21:21:50 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	spce_available;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	spce_available = dstsize - dstlen - 1;
	if (dstsize == 0 || dstlen >= dstsize)
		return (dstsize + srclen);
	while (*dst)
		dst++;
	if (spce_available > srclen)
	{
		ft_memcpy(dst, src, srclen);
		dst[srclen] = '\0';
	}
	else
	{
		ft_memcpy(dst, src, spce_available);
		dst[spce_available] = '\0';
	}
	return (dstlen + srclen);
}
