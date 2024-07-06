/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:45:56 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/04 10:57:21 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_white(int c)
{
	if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
		|| c == '\f')
		return (1);
	return (0);
}

int	ft_atoi_rgb(char **str)
{
	int	nb;

	nb = 0;
	while (is_white(**str))
		(*str)++;
	if (**str == '-')
		ft_error();
	if (**str == '+')
		(*str)++;
	while (ft_isdigit(**str))
	{
		nb = (nb * 10) + (((**str) - '0'));
		if (nb > 255)
			ft_error();
        (*str)++;
	}
	return (nb);
}
