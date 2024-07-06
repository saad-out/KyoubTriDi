/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:45:56 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/06 10:11:47 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_extension(char *filename)
{
	int	i;

	i = 0;
	while (filename[i] != '\0')
		i++;
	if (filename[i - 1] != 'b' || filename[i - 2] != 'u' || filename[i
		- 3] != 'c' || filename[i - 4] != '.')
		ft_error();
}

void	skip_digits(char **line)
{
	while (ft_isdigit(**line))
		(*line)++;
}

void	skip_whitespace(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

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
