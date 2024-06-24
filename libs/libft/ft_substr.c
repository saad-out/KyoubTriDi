/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:05:29 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/01 11:17:08 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
		len = 0;
	else if (len > slen || (start + len > slen))
		len = slen - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (len && len-- > 0)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
