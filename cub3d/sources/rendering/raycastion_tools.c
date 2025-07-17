/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastion_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:07:14 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/17 11:13:10 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

float distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void draw_line(t_game *game, float x1, float y1, float x2, float y2)
{
	t_line	line;
	
	line.dx = x2 - x1;
	line.dy = y2 - y1;
    if (fabs(line.dx) > fabs(line.dy))
        line.steps = fabs(line.dx);
    else
        line.steps = fabs(line.dy);
	 if (line.steps == 0)
	{
        my_mlx_pixel_put(game, round(x1), round(y1), 0x00FF0000);
        return;
    }
    line.x_inc = line.dx / (float)line.steps;
    line.y_inc = line.dy / (float)line.steps;
    line.x = x1;
    line.y = y1;
    for (int i = 0; i <= line.steps; i++)
    {
        if (line.x >= 0 && line.x < WINDOW_WIDTH&& line.y >= 0 && line.y < WINDOW_HEIGHT)
        	my_mlx_pixel_put(game, round(line.x), round(line.y), 0x652424);
		line.x += line.x_inc;
		line.y += line.y_inc;
    }
}

void	initiatize_rayfacing(t_game *game, float ray_angle, int i)
{
	game->rays[i].is_ray_facing_down = ray_angle > 0 && ray_angle < PI; // [0-180]
	game->rays[i].is_ray_facing_up = !game->rays[i].is_ray_facing_down;
	game->rays[i].is_ray_facing_left =  ray_angle > (PI / 2) && ray_angle < (1.5 * PI); // [90-270], [(PI / 2)-(3PI / 2)]
	game->rays[i].is_ray_facing_right = !game->rays[i].is_ray_facing_left;
}

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
void	store_final_hit(t_game *game, float h_dist, float v_dist, int i)
{
		if (v_dist < h_dist)
	{
		game->rays[i].distance = v_dist;
		game->rays[i].wall_hit_x = game->rays[i].verthit_x;
		game->rays[i].wall_hit_y = game->rays[i].verthit_y;
		game->rays[i].was_hit_vertical = true;
	}
	else 
	{
		game->rays[i].distance = h_dist;
		game->rays[i].wall_hit_x = game->rays[i].horzhit_x;
		game->rays[i].wall_hit_y = game->rays[i].horzhit_y;
		game->rays[i].was_hit_vertical = false;
	}
} 



