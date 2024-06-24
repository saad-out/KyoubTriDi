/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:08:43 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/05 11:22:05 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	const char	*s;

	i = 0;
	s = src;
	if (dstsize == 0)
		return (ft_strlen(src));
	while ((i++ < (dstsize - 1)) && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (ft_strlen(s));
}
