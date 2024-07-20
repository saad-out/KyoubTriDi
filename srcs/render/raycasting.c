/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 04:14:03 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/19 02:34:238 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_point ver_intersection_distance(t_ray ray, t_player *player)
{
    t_point point;
    double  xIntercept;
    double  yIntercept;
    double  xStep;
    double  yStep;

    // find vertical (y/x)(inter/step) values
    xIntercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    if (ray.facingRight)
        xIntercept += TILE_SIZE;
    yIntercept = player->y + ((xIntercept - player->x) * tan(ray.angle));
    xStep = TILE_SIZE;
    if (!ray.facingRight)
        xStep *= -1;
    yStep = xStep * tan(ray.angle);
    if ((yStep > 0 && ray.facingUp) || (yStep < 0 && !ray.facingUp))
        yStep *= -1;
    
    // find vertical intersection
    point.x = xIntercept;
    point.y = yIntercept;
    if (!ray.facingRight)
        point.x--;
    while ((point.x > 0 && point.x < WIDTH) && (point.y > 0 && point.y < HEIGHT))
    {
        if (is_wall(point.x, point.y, get_data(NULL)))
            break ;
        else
        {
            point.x += xStep;
            point.y += yStep;
        }
    }
    return (point);
}

t_point hor_intersection_distance(t_ray ray, t_player *player)
{
    t_point point;
    double  xIntercept;
    double  yIntercept;
    double  xStep;
    double  yStep;

    // find horizontal (y/x)(inter/step) values
    yIntercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    if (!ray.facingUp)
        yIntercept += TILE_SIZE;
    xIntercept = player->x + ((yIntercept - player->y) / tan(ray.angle));
    yStep = TILE_SIZE;
    if (ray.facingUp)
        yStep *= -1;
    xStep = yStep / tan(ray.angle);
    if ((xStep > 0 && !ray.facingRight) || (xStep < 0 && ray.facingRight))
        xStep *= -1;

    // find horizontal intersection
    point.x = xIntercept;
    point.y = yIntercept;
    if (ray.facingUp)
        point.y--;
    while ((point.x > 0 && point.x < WIDTH) && (point.y > 0 && point.y < HEIGHT))
    {
        if (is_wall(point.x, point.y, get_data(NULL)))
            break ;
        else
        {
            point.x += xStep;
            point.y += yStep;
        }
    }
    return point;
}

void cast_rays(t_mlx *mlx, t_player *player) {
    t_data *data = get_data(NULL);
    double rayangle = player->rotationAngle - FOV / 2;
    double angle_inc = FOV / (double)NUM_RAYS;

    t_ray   ray[NUM_RAYS];

    // printf("Player Angle: %f, Initial Ray Angle: %f\n", player->rotationAngle, rayangle);
    // printf("Angle Increment: %f\n", angle_inc);

    // calculate rays' distances
    for (int i = 0; i < NUM_RAYS; i++) {
        rayangle = normalizeAngle(rayangle);
        ray[i].angle = rayangle;
        if (ray[i].angle > PI)
            ray[i].facingUp = true;
        else
            ray[i].facingUp = false;
        if (ray[i].angle < (PI / 2) || ray[i].angle > ((3 * PI) / 2))
            ray[i].facingRight = true;
        else
            ray[i].facingRight = false;

        // printf(" ===========> Ray facingUp: %d facingRight: %d ==========>\n", ray[i].facingUp, ray[i].facingRight);

        t_point horInter = hor_intersection_distance(ray[i], player);
        t_point verInter = ver_intersection_distance(ray[i], player);
        t_point min = min_point(horInter, verInter, player);
        // check if the ray hit a vertical wall or a horizontal wall
        if (equal_points(min, verInter))
            ray[i].wasHitVertical = true;
        else
            ray[i].wasHitVertical = false;
        // printf("============ (%2.f,%2.f) (%2.f,%2.f) MIN is =>(%2.f,%2.f)\n", horInter.x, horInter.y, verInter.x, verInter.y, min.x, min.y);

        ray[i].intersection = min;
        t_point tmp;
        tmp.x = player->x;
        tmp.y = player->y;
        ray[i].distance = distance(tmp, min);
        // printf("****** distanceAA: %f\n", ray[i].distance);

        rayangle += angle_inc;
    }

    //3D raycasting
    for (int i = 0; i < NUM_RAYS; i++)
    {
        double  correctedDistance = ray[i].distance * cos(ray[i].angle - player->rotationAngle);
        double  distProjPlane = ((double)WIDTH / 2) / tan(FOV / 2);
        double  wallStripHeight = ((double)TILE_SIZE / correctedDistance) * distProjPlane;

        // printf("=====> wall strip height: %f\n", wallStripHeight);

        // draw ceiling
        ft_draw_line(mlx,
                        i,
                        0,
                        i,
                        (HEIGHT / 2) - (wallStripHeight / 2),
                        0x0087CEFA);

        double alpha = 1000 / correctedDistance;
        ft_draw_line(mlx,
                        i,
                        (HEIGHT / 2) - (wallStripHeight / 2),
                        i,
                        (HEIGHT / 2) + (wallStripHeight / 2),
                        0x00000080 + alpha);


                /// TEXTURE MAPPING
        // int texelX;
        // if (ray[i].wasHitVertical)
        //     texelX = (int)ray[i].intersection.y % TILE_SIZE;
        // else
        //     texelX = (int)ray[i].intersection.x % TILE_SIZE;
        // double wallTop = (HEIGHT / 2) - (wallStripHeight / 2);
        // double wallBottom = (HEIGHT / 2) + (wallStripHeight / 2);
        // for (int y = (int)wallTop; y < (int)wallBottom; y++)
        // {
        //     int texelY = (y - wallTop) * ((double)TILE_SIZE / wallStripHeight);
        //     int index = texelY * TILE_SIZE + texelX;
        //     int color = data->map_data->no_texture[index];
        //     my_mlx_pixel_put(&mlx->img, i, y, color);
        // }
                /// TEXTURE MAPPING

        // draw floor
        ft_draw_line(mlx,
                        i,
                        (HEIGHT / 2) + (wallStripHeight / 2),
                        i,
                        HEIGHT,
                        0x00DEB887);
    }

    // Draw map
	ft_render_map(data->mlx, data->map_data);
    for (int i = 0; i < NUM_RAYS; i++)
    {
        ft_draw_circle(mlx,
                        player->x * MINIMAP_SCALE,
                        player->y * MINIMAP_SCALE,
                        player->radius * MINIMAP_SCALE,
                        0x00065535);
        ft_draw_line(mlx,
                        player->x * MINIMAP_SCALE,
                        player->y * MINIMAP_SCALE,
                        (player->x + cos(player->rotationAngle) * 20) * MINIMAP_SCALE,
                        (player->y + sin(player->rotationAngle) * 20) * MINIMAP_SCALE,
                        0x00FFFF00);
        ft_draw_line(mlx,
                        player->x * MINIMAP_SCALE,
                        player->y * MINIMAP_SCALE,
                        ray[i].intersection.x * MINIMAP_SCALE,
                        ray[i].intersection.y * MINIMAP_SCALE,
                        0x00000000);
    }
}

