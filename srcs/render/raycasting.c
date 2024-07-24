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

    t_data *data = get_data(NULL);
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
    // while ((point.x > 0 && point.x < WIDTH) && (point.y > 0 && point.y < HEIGHT))
    while ((point.x > 0 && point.x < data->map_data->map.cols * TILE_SIZE) && (point.y > 0 && point.y < data->map_data->map.rows * TILE_SIZE))
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

    t_data *data = get_data(NULL);
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
    while ((point.x > 0 && point.x < data->map_data->map.cols * TILE_SIZE) && (point.y > 0 && point.y < data->map_data->map.rows * TILE_SIZE))
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

int    get_texture_color(int x, int y, t_img texture)
{
    int color;
    int *addr;

    addr = (int *)texture.addr;
    color = addr[y * texture.width + x];
    return (color);
}

int is_same(double a, double b)
{
    double EPSILON = 0.001;
    return (fabs(a - b) < EPSILON);
}

void cast_rays(t_mlx *mlx, t_player *player) {
    t_data *data = get_data(NULL);
    double rayangle = player->rotationAngle - FOV / 2;
    double angle_inc = (double)FOV / (double)NUM_RAYS;

    t_ray   ray[NUM_RAYS];

    // calculate rays' distances
    for (int i = 0; i < NUM_RAYS; i++) {
        rayangle = normalizeAngle(rayangle);
        ray[i].angle = rayangle;
        set_ray_angle(&ray[i]);

        // find horizontal and vertical intersection points
        t_point horInter = hor_intersection_distance(ray[i], player);
        t_point verInter = ver_intersection_distance(ray[i], player);
        // printf("horX: %f horY: %f verX: %f verY: %f\n", horInter.x, horInter.y, verInter.x, verInter.y);

        // find the closest intersection point
        t_point min = min_point(horInter, verInter, player);
        ray[i].intersection = min;

        // set distance
        t_point tmp;
        tmp.x = player->x;
        tmp.y = player->y;
        ray[i].distance = distance(tmp, min);
        
        if (equal_points(min, verInter))
        {
            // print VER in green
            // printf(GREEN"horx: %.2f hory: %.2f verx: %.2f very: %.2f difference: (%f) => VER\n\n"RESET, horInter.x, horInter.y, verInter.x, verInter.y, ray[i].distance);
            ray[i].wasHitVertical = true;
        }
        else
        {
            // print HOR in red
            // printf(RED"horx: %.2f hory: %.2f verx: %.2f very: %.2f difference: (%f) => HOR\n\n"RESET, horInter.x, horInter.y, verInter.x, verInter.y, ray[i].distance);
            ray[i].wasHitVertical = false;
        }


        // increment angle
        rayangle += angle_inc;
    }

    //3D raycasting
    for (int i = 0; i < NUM_RAYS; i++)
    {
        // compute wall height
        double  correctedDistance = ray[i].distance * cos(ray[i].angle - player->rotationAngle);
        double  distProjPlane = ((double)WIDTH / 2) / tan(FOV / 2);
        double  wallStripHeight = ((double)TILE_SIZE / correctedDistance) * distProjPlane;

        // set texture
        t_img   texture;
        set_texture(ray[i], data, &texture);

        // set start and end points of the wall strip
        int wallTop = (HEIGHT / 2) - (wallStripHeight / 2);
        int wallBottom = (HEIGHT / 2) + (wallStripHeight / 2);
        if (wallTop < 0)
            wallTop = 0;
        if (wallBottom > HEIGHT)
            wallBottom = HEIGHT;

        // draw ceiling
        ft_draw_line(mlx,
                        i,
                        0,
                        i,
                        wallTop,
                        0x0087CEFA);

                /// TEXTURE MAPPING

            
        int texelX;
        if (ray[i].wasHitVertical)
            texelX = (int)ray[i].intersection.y % TILE_SIZE;
        else
            texelX = (int)ray[i].intersection.x % TILE_SIZE;

        // Scale texelX to the texture width
        texelX = (texelX * texture.width) / TILE_SIZE;

        for (int y = wallTop; y < wallBottom; y++)
        {
            int distanceFromTop = y + (wallStripHeight / 2) - (HEIGHT / 2);
            // int texelY = distanceFromTop * ((double)texture.height / wallStripHeight);
            int texelY = (1LL* distanceFromTop * texture.height + wallStripHeight/2)/ wallStripHeight;

            // Ensure texelY stays within the texture height bounds
            texelY = texelY % texture.height;

            int color = get_texture_color(texelX, texelY, texture);
            my_mlx_pixel_put(&mlx->img, i, y, color);
        }
        // TEXTURE MAPPING

        // draw floor
        ft_draw_line(mlx,
                        i,
                        wallBottom,
                        i,
                        HEIGHT,
                        0x00DEB887);
    }

    // Draw map
	ft_render_map(data->mlx, data->map_data);
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
    for (int i = 0; i < NUM_RAYS; i++)
    {
        ft_draw_line(mlx,
                        player->x * MINIMAP_SCALE,
                        player->y * MINIMAP_SCALE,
                        ray[i].intersection.x * MINIMAP_SCALE,
                        ray[i].intersection.y * MINIMAP_SCALE,
                        0x00000000);
    }
}

