/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:16:28 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/07 16:15:53 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (i < n && big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while ((i < n) && big[i++] == little[j++])
			{
				if (little[j] == '\0')
					return ((char *)&big[i - j]);
			}
			i -= j;
		}
		i++;
	}
	return (NULL);
}
