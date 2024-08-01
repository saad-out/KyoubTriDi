/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:23:01 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/01 12:05:36 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_empty_line(char final_char_line)
{
	if (final_char_line == '\n' || final_char_line == '\0')
		return (true);
	return (false);
}

void	add_path(char **identifier, char *path, int *elemts)
{
	check_extension_textures(path);
	check_path(path);
	if (*identifier)
		ft_error();
	*identifier = ft_strdup(path);
	(*elemts)++;
}

void	add_color(int *color, char *joined, int *elemts)
{
	if (*color != -1)
		ft_error();
	*color = get_color(joined);
	(*elemts)++;
}
