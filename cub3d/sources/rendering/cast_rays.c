/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:14:57 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/16 13:26:41 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


/**
 * I- cast_rays:
 
    1- get the ray angle (where the casting of rays start), ray_angle = player angle of rotation
	   half of his field of vie 
	2- number of rays to cast = the width of he window 
	3- whil we have rays to cast -> cast one ray -> move to the next ray by moving the ray_angle
	  to the next ray
	
	II- cast_one_ray
		1- find horizental hill to wall
			
	
*/

bool	hit_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return (true);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_x >= game->map.width
		|| map_y < 0 || map_y >= game->map.height)
	return (true);
	return (game->map.grid[map_y][map_x] == '1');
}

void	initiatize_rayfacing(t_game *game, float ray_angle, int i)
{
	game->rays[i].is_ray_facing_down = ray_angle > 0 && ray_angle < PI; // [0-180]
	game->rays[i].is_ray_facing_up = !game->rays[i].is_ray_facing_down;
	game->rays[i].is_ray_facing_left =  ray_angle > (PI / 2) && ray_angle < (1.5 * PI); // [90-270], [(PI / 2)-(3PI / 2)]
	game->rays[i].is_ray_facing_right = !game->rays[i].is_ray_facing_left;
}

bool	find_horizontal_intersection(t_game *game, float ray_angle, int i)
{
	float	y_intercept;
	float	x_intercept;
	float	x_step;
	float	y_step;
	float	next_x;
	float	next_y;
	
	initiatize_rayfacing(game, ray_angle, i);
	y_intercept = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	if (game->rays[i].is_ray_facing_down)
		y_intercept += TILE_SIZE;
	x_intercept = game->player.x + (y_intercept - game->player.y) / tan(ray_angle);
	y_step = TILE_SIZE;
	if (game->rays[i].is_ray_facing_up)
		y_step *= -1;
	x_step = TILE_SIZE / tan(ray_angle);
	if (game->rays[i].is_ray_facing_left && x_step > 0)
		x_step *= -1;
	if (game->rays[i].is_ray_facing_right && x_step < 0)
		x_step *= -1;
	
	// looping to get the x && y the the first horz hit wall

	next_x = x_intercept;
	next_y = y_intercept;
	while (next_x >= 0 && next_x <= WINDOW_WIDTH
		&& next_y >= 0 && next_y <= WINDOW_HEIGHT)
	{
		float y_to_check = next_y;
		if (game->rays[i].is_ray_facing_up)
    		y_to_check -= 1; // Look at the pixel in the tile above the line
		if (hit_wall(game, next_x, y_to_check))
		{
			game->rays[i].horzhit_x = next_x;
			game->rays[i].horzhit_y = next_y;
			return (true);
			
		}
		next_x += x_step;
		next_y += y_step;
	}
	return (false);
}

bool	find_vertocal_intersection(t_game *game, float ray_angle, int i)
{
	float	y_intercept;
	float	x_intercept;
	float	x_step;
	float	y_step;
	float	next_x;
	float	next_y;
	
	initiatize_rayfacing(game, ray_angle, i);
	x_intercept = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	if (game->rays[i].is_ray_facing_right)
		x_intercept += TILE_SIZE;
	y_intercept = game->player.y + (x_intercept - game->player.x) * tan(ray_angle);
	x_step = TILE_SIZE;
	if (game->rays[i].is_ray_facing_left)
		x_step *= -1;
	y_step = TILE_SIZE * tan(ray_angle);
	if (game->rays[i].is_ray_facing_up && y_step > 0)
		y_step *= -1;
	if (game->rays[i].is_ray_facing_down && y_step < 0)
		y_step *= -1;
	
	next_x = x_intercept;
	next_y = y_intercept;

	while (next_x >= 0 && next_x <= WINDOW_WIDTH
		&& next_y >= 0 && next_y <= WINDOW_HEIGHT)
	{
		float x_to_check = next_x;
		if (game->rays[i].is_ray_facing_left)
    		x_to_check -= 1;
		if (hit_wall(game, x_to_check, next_y))
		{
			game->rays[i].verthit_x = next_x;
			game->rays[i].verthit_y = next_y;
			return (true);
			
		}
		next_x += x_step;
		next_y += y_step;
	}
	return (false);
}

float distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void draw_line(t_game *game, float x1, float y1, float x2, float y2)
{
    float   dx = x2 - x1;
    float   dy = y2 - y1;
    int     steps;
    float   x_inc, y_inc;
    float   x, y;

    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
	 if (steps == 0)
	{
        my_mlx_pixel_put(game, round(x1), round(y1), 0x00FF0000);
        return;
    }

    x_inc = dx / (float)steps;
    y_inc = dy / (float)steps;

    x = x1;
    y = y1;
    for (int i = 0; i <= steps; i++)
    {
        if (x >= 0 && x < WINDOW_WIDTH&& y >= 0 && y < WINDOW_HEIGHT)
        	my_mlx_pixel_put(game, round(x), round(y), 0x652424);
		x += x_inc;
		y += y_inc;
    }
}

void	cast_one_ray(t_game *game , float ray_angle, int i)
{
	float horz_hit_distance;
	float vert_hit_distance;

	horz_hit_distance = 1e30;
    vert_hit_distance = 1e30;
	ray_angle = normalize_angle(ray_angle);
	if (find_horizontal_intersection(game, ray_angle, i)){
		horz_hit_distance = distance(game->player.x, game->player.y,
			game->rays[i].horzhit_x, game->rays[i].horzhit_y);
	}
	if (find_vertocal_intersection(game, ray_angle, i)){
		vert_hit_distance = distance(game->player.x, game->player.y,
			game->rays[i].verthit_x, game->rays[i].verthit_y);
	}
	if (vert_hit_distance < horz_hit_distance)
	{
		game->rays[i].distance = vert_hit_distance;
		game->rays[i].wall_hit_x = game->rays[i].verthit_x;
		game->rays[i].wall_hit_y = game->rays[i].verthit_y;
		game->rays[i].was_hit_vertical = true;
	}
	else 
	{
		game->rays[i].distance = horz_hit_distance;
		game->rays[i].wall_hit_x = game->rays[i].horzhit_x;
		game->rays[i].wall_hit_y = game->rays[i].horzhit_y;
		game->rays[i].was_hit_vertical = false;
	}
	game->rays[i].ray_angle = ray_angle;
}

void	cast_rays(t_game *game)
{
	float	ray_angle;
	int		num_rays;
	int		i;

	ray_angle = game->player.rotation_angle - (FOV / 2);
	num_rays = WINDOW_WIDTH;
	i = 0;
	while (i < num_rays)
	{
		cast_one_ray(game, ray_angle, i);
		ray_angle += FOV / num_rays;
		i++;
	}
	
}
