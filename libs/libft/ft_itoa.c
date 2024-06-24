/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:55:43 by klakbuic          #+#    #+#             */
/*   Updated: 2023/11/07 16:12:35 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	nb_count(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	itoa_copy(char **nb_str, size_t len, unsigned int nb)
{
	if (nb == 0)
		(*nb_str)[--len] = (nb % 10) + '0';
	while (nb != 0)
	{
		(*nb_str)[--len] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	char			*nb_str;
	int				len;
	int				signe;
	unsigned int	nb;

	len = 0;
	signe = 1;
	nb = n;
	if (n < 0)
	{
		nb = -n;
		len = 1;
		signe = -1;
	}
	len += nb_count(nb);
	nb_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!nb_str)
		return (NULL);
	nb_str[len] = '\0';
	if (signe == -1)
		nb_str[0] = '-';
	itoa_copy(&nb_str, len, nb);
	return (nb_str);
}
