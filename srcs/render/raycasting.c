/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 04:14:03 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/18 02:11:19 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define FOV (60 * (PI / 180)) // 60 degrees in radians
#define NUM_RAYS (WIDTH / 50)

void cast_rays(t_mlx *mlx, t_player *player) {
    double rayangle = player->rotationAngle - FOV / 2;

    printf("Player Angle: %f, Initial Ray Angle: %f\n", player->rotationAngle, rayangle);
    // printf("Angle Increment: %f\n", angle_inc);

    for (int i = 0; i < NUM_RAYS; i++) {
        double ray_x = player->x + cos(rayangle) * 50;
        double ray_y = player->y + sin(rayangle) * 50;
        printf("Ray %d: angle %f, end point (%f, %f)\n", i, rayangle, ray_x, ray_y);
        ft_draw_line(mlx, player->x, player->y, ray_x, ray_y, 0x00000000);
        double angle_inc = FOV / (double)NUM_RAYS;
        rayangle += angle_inc;
    }
}

