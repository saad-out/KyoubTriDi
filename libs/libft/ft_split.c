/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:39:47 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/08 09:44:02 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	fix_leaks(char **strs, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(strs[j]);
		j++;
	}
	free(strs);
	return (1);
}

static size_t	words_count(char *s, char c)
{
	size_t	nb;
	size_t	i;

	if (!s)
		return (0);
	nb = 0;
	i = 1;
	while (*s == c && *s)
		s++;
	while (*s && s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			nb++;
		else if (s[i] != c && s[i + 1] == '\0')
			nb++;
		i++;
	}
	return (nb);
}

static size_t	len_count(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**strs;
	size_t	words;
	size_t	i;

	str = (char *)s;
	words = words_count(str, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while ((*str == c && *str != '\0'))
			str++;
		strs[i] = (char *)malloc(sizeof(char) * (len_count(str, c) + 1));
		if (!strs[i] && fix_leaks(strs, i))
			return (NULL);
		ft_memcpy(strs[i], str, len_count(str, c));
		strs[i++][len_count(str, c)] = '\0';
		while ((*str != c && *str != '\0'))
			str++;
	}
	strs[i] = NULL;
	return (strs);
}
