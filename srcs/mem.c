/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:52:33 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/03 09:52:46 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}