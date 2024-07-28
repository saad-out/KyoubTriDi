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

t_point ver_intersection_distance(t_ray *ray, t_player *player)
{
    t_point point;
    double  xIntercept;
    double  yIntercept;
    double  xStep;
    double  yStep;

    t_data *data = get_data(NULL);
    // find vertical (y/x)(inter/step) values
    xIntercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    if (ray->facingRight)
        xIntercept += TILE_SIZE;
    yIntercept = player->y + ((xIntercept - player->x) * tan(ray->angle));
    xStep = TILE_SIZE;
    if (!ray->facingRight)
        xStep *= -1;
    yStep = xStep * tan(ray->angle);
    if ((yStep > 0 && ray->facingUp) || (yStep < 0 && !ray->facingUp))
        yStep *= -1;
    
    // find vertical intersection
    point.x = xIntercept;
    point.y = yIntercept;
    if (!ray->facingRight)
        point.x -= EPSILON;
        // point.x--;
    while ((point.x > 0 && point.x < data->map_data->map.cols * TILE_SIZE) && (point.y > 0 && point.y < data->map_data->map.rows * TILE_SIZE))
    {
        if (is_wall_2(point.x, point.y, get_data(NULL)))
            break ;
        else
        {
            point.x += xStep;
            point.y += yStep;
        }
    }
    if (point.x < 0)
        point.x = 0;
    else if (point.x > data->map_data->map.cols * TILE_SIZE)
        point.x = (data->map_data->map.cols * TILE_SIZE) - 1;
    if (point.y < 0)
        point.y = 0;
    else if (point.y > data->map_data->map.rows * TILE_SIZE)
        point.y = (data->map_data->map.rows * TILE_SIZE) - 1;
    return (point);
}

t_point hor_intersection_distance(t_ray *ray, t_player *player)
{
    t_point point;
    double  xIntercept;
    double  yIntercept;
    double  xStep;
    double  yStep;

    t_data *data = get_data(NULL);
    // find horizontal (y/x)(inter/step) values
    yIntercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    if (!ray->facingUp)
        yIntercept += TILE_SIZE;
    xIntercept = player->x + ((yIntercept - player->y) / tan(ray->angle));
    yStep = TILE_SIZE;
    if (ray->facingUp)
        yStep *= -1;
    xStep = yStep / tan(ray->angle);
    if ((xStep > 0 && !ray->facingRight) || (xStep < 0 && ray->facingRight))
        xStep *= -1;

    // find horizontal intersection
    point.x = xIntercept;
    point.y = yIntercept;
    if (ray->facingUp)
        point.y -= EPSILON;
        // point.y--;
    while ((point.x > 0 && point.x < data->map_data->map.cols * TILE_SIZE) && (point.y > 0 && point.y < data->map_data->map.rows * TILE_SIZE))
    {
        if (is_wall_2(point.x, point.y, get_data(NULL)))
            break ;
        else
        {
            point.x += xStep;
            point.y += yStep;
        }
    }
    if (point.x < 0)
        point.x = 0;
    else if (point.x > data->map_data->map.cols * TILE_SIZE)
        point.x = (data->map_data->map.cols * TILE_SIZE) - 1;
    if (point.y < 0)
        point.y = 0;
    else if (point.y > data->map_data->map.rows * TILE_SIZE)
        point.y = (data->map_data->map.rows * TILE_SIZE) - 1;
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
    return (fabs(a - b) < EPSILON);
}

void    cast_ray(t_player *player, t_ray *ray, double rayangle)
{
    set_ray_angle(ray, rayangle);

    // find horizontal and vertical intersection points
    t_point horInter = hor_intersection_distance(ray, player);
    t_point verInter = ver_intersection_distance(ray, player);

    // find the closest intersection point
    t_point min = min_point(horInter, verInter, player);
    ray->intersection.x = min.x;
    ray->intersection.y = min.y;

    // set distance
    t_point tmp;
    tmp.x = player->x;
    tmp.y = player->y;
    ray->distance = distance(tmp, min);
    if (equal_points(min, verInter))
        ray->wasHitVertical = true;
    else
        ray->wasHitVertical = false;
}

void    draw_wallStrip(t_mlx *mlx, t_player *player, t_ray *ray, int i)
{
    t_data  *data = get_data(NULL);
    double  correctedDistance = ray->distance * cos(ray->angle - player->rotationAngle);
    double  distProjPlane = ((double)WIDTH / 2) / tan(FOV / 2);
    double  wallStripHeight = ((double)TILE_SIZE / correctedDistance) * distProjPlane;

    // set texture
    t_img   texture;
    set_texture(ray, data, &texture);

    // set start and end points of the wall strip
    int wallTop = (HEIGHT / 2) - (wallStripHeight / 2);
    int wallBottom = (HEIGHT / 2) + (wallStripHeight / 2);
    if (wallTop < 0)
        wallTop = 0;
    if (wallBottom < 0 || wallBottom > HEIGHT)
        wallBottom = HEIGHT;

    // draw ceiling
    // printf("%d ceil 0 -> %d\n", i, wallTop);
    ft_draw_line(mlx,
                    i,
                    0,
                    i,
                    wallTop,
                    0x0087CEFA);

            /// TEXTURE MAPPING

        
    int texelX;
    if (ray->wasHitVertical)
        texelX = (int)ray->intersection.y % TILE_SIZE;
    else
        texelX = (int)ray->intersection.x % TILE_SIZE;

    // Scale texelX to the texture width
    texelX = (texelX * texture.width) / TILE_SIZE;

    // printf("%d text %d -> %d\n", i, wallTop, wallBottom);
    for (int y = wallTop; y < wallBottom; y++)
    {
        int distanceFromTop = y + (wallStripHeight / 2) - (HEIGHT / 2);
        int texelY = (1LL* distanceFromTop * texture.height + wallStripHeight/2)/ wallStripHeight;

        // Ensure texelY stays within the texture height bounds
        texelY = texelY % texture.height;
        // if (y % 4 == 0)
        //     printf(YELLOW"diTop = %d texelY: %d => (%d,%d)\n"RESET, distanceFromTop, (1LL* distanceFromTop * texture.height + wallStripHeight/2)/ wallStripHeight, texelX, texelY);

        int color = get_texture_color(texelX, texelY, texture);
        my_mlx_pixel_put(&mlx->img, i, y, color);
    }
    // TEXTURE MAPPING

    // draw floor
    // printf("floor %d (%d, %d)\n", i, wallBottom, HEIGHT);
    ft_draw_line(mlx,
                    i,
                    wallBottom,
                    i,
                    HEIGHT,
                    0x00DEB887);
    // printf("safe %d\n\n", i);

}

void    draw_minimap(t_data *data, t_player *player)
{
	ft_render_map(data->mlx, data->map_data);
    ft_draw_circle(data->mlx,
                    player->x * MINIMAP_SCALE,
                    player->y * MINIMAP_SCALE,
                    player->radius * MINIMAP_SCALE,
                    0x00065535);
    ft_draw_line(data->mlx,
                    player->x * MINIMAP_SCALE,
                    player->y * MINIMAP_SCALE,
                    (player->x + cos(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE,
                    (player->y + sin(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE,
                    0x00000000);
}

void cast_rays(t_mlx *mlx, t_player *player) {
    t_data *data = get_data(NULL);
    double rayangle = player->rotationAngle - FOV / 2;
    double angle_inc = (double)FOV / (double)NUM_RAYS;
    int i;

    t_ray   ray[NUM_RAYS];

    // calculate rays' distances
    i = 0;
    while (i < NUM_RAYS)
    {
        rayangle = normalizeAngle(rayangle);
        cast_ray(player, &ray[i++], rayangle);
        rayangle += angle_inc;
    }

    //3D raycasting
    i = -1;
    while (++i < NUM_RAYS)
        draw_wallStrip(mlx, player, &ray[i], i);

    // Draw map
    draw_minimap(data, player);
}

