/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:00:27 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/05 21:25:24 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BEGIN 0

static char	*skip_white(char const *s1, char const *set)
{
	s1 = (char *)s1;
	while (*s1)
	{
		if (ft_strchr(set, *s1))
			s1++;
		else
			break ;
	}
	return ((char *)s1);
}

static size_t	get_end_index(char const *s1, char const *set)
{
	size_t	len;

	len = ft_strlen(s1);
	while (len-- > 0)
		if (!ft_strchr(set, s1[len]))
			break ;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	str = skip_white(s1, set);
	end = get_end_index(str, set) + 1;
	str = ft_substr(str, BEGIN, end);
	if (!str)
		return (NULL);
	return (str);
}
