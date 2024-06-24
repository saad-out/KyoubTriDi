/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:06:18 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/06 14:17:58 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;

	s = NULL;
	while (*str)
	{
		if (*str == (unsigned char)c)
			s = (char *)str;
		str++;
	}
	if (*str == (unsigned char)c)
		return ((char *)str);
	return (s);
}
