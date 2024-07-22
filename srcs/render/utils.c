/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 02:55:56 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/22 05:43:23 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double  normalizeAngle(double angle)
{
    double new;

    new = fmod(angle, 2 * PI);
    if (new < 0)
        new += 2 * PI;
    return new;
}

double distance(t_point a, t_point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

t_point min_point(t_point a, t_point b, t_player *player) {
    t_point p;
    p.x = player->x;
    p.y = player->y;
    double dist_a = distance(p, a);
    double dist_b = distance(p, b);
    // if (dist_a < dist_b)
    //     printf("****** distance: %f\n", dist_a);
    // else
    //     printf("****** distance: %f\n", dist_b);
    return dist_a < dist_b ? a : b;
}

bool equal_points(t_point a, t_point b) {
    return a.x == b.x && a.y == b.y;
}
