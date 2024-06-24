/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*           q                                         +:+ +:+
	+:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:11:12 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/01 17:54:42 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	char	*nstr;

	nstr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!nstr)
		return (NULL);
	ft_memcpy(nstr, str, (ft_strlen(str) + 1));
	return (nstr);
}
