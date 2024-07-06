/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:33:27 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/06 09:02:20 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	i = 0;
	if (start > slen)
		return (NULL);
	else if (len == 0 || len > slen || (start + len > slen))
		return (NULL);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (len && len-- > 0)
	{
		sub[i++] = s[start++];
	}
	sub[i] = '\0';
	return (sub);
}

size_t	ft_strlen(const char *str)
{
	const char	*p;

	p = str;
	while (*str != '\0')
		str++;
	return ((str - p));
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int					i;
	unsigned char		*dst;
	const unsigned char	*sc;

	if (!dest && !src)
		return (dest);
	i = 0;
	dst = dest;
	sc = src;
	if (n != 0)
	{
		while (n-- > 0)
		{
			dst[i] = sc[i];
			i++;
		}
	}
	return (dst);
}

int	is_found(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
		if (buff[i++] == '\n')
			return (1);
	return (0);
}

int	nl_index(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
		if (buff[i++] == '\n')
			return (i);
	return (i);
}