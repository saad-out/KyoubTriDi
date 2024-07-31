/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:34:55 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/30 12:15:35 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_ea(char **splited)
{
	if (ft_strcmp(splited[0], "EA") == 0 && splited[1] && (!splited[2]
			|| (splited[2] && ft_strcmp(splited[2], "\n") == 0)))
	{
		return (true);
	}
	return (false);
}

bool	is_we(char **splited)
{
	if (ft_strcmp(splited[0], "WE") == 0 && splited[1] && (!splited[2]
			|| (splited[2] && ft_strcmp(splited[2], "\n") == 0)))
	{
		return (true);
	}
	return (false);
}

bool	is_so(char **splited)
{
	if (ft_strcmp(splited[0], "SO") == 0 && splited[1] && (!splited[2]
			|| (splited[2] && ft_strcmp(splited[2], "\n") == 0)))
	{
		return (true);
	}
	return (false);
}

bool	is_no(char **splited)
{
	if (ft_strcmp(splited[0], "NO") == 0 && splited[1] && (!splited[2]
			|| (splited[2] && ft_strcmp(splited[2], "\n") == 0)))
	{
		return (true);
	}
	return (false);
}
