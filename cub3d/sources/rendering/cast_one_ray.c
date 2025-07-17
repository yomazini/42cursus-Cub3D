/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_one_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:10:41 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/17 11:13:01 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_horizontal_dda(t_game *game, t_dda *dda, int i)
{
	dda->y_intercept = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	if (game->rays[i].is_ray_facing_down)
		dda->y_intercept += TILE_SIZE;
	dda->x_intercept = game->player.x + (dda->y_intercept - game->player.y) / tan(game->rays[i].ray_angle);
	dda->y_step = TILE_SIZE;
	if (game->rays[i].is_ray_facing_up)
		dda->y_step *= -1;
	dda->x_step = TILE_SIZE / tan(game->rays[i].ray_angle);
	if (game->rays[i].is_ray_facing_left && dda->x_step > 0)
		dda->x_step *= -1;
	if (game->rays[i].is_ray_facing_right && dda->x_step < 0)
		dda->x_step *= -1;
	dda->next_x = dda->x_intercept;
	dda->next_y = dda->y_intercept;
}


static bool	find_horizontal_intersection(t_game *game, int i)
{
	t_dda	dda;
	
	initiatize_rayfacing(game, game->rays[i].ray_angle, i);
	init_horizontal_dda(game, &dda, i);
	while (dda.next_x >= 0 && dda.next_x <= WINDOW_WIDTH
		&& dda.next_y >= 0 && dda.next_y <= WINDOW_HEIGHT)
	{
		float y_to_check = dda.next_y;
		if (game->rays[i].is_ray_facing_up)
    		y_to_check -= 1;
		if (hit_wall(game, dda.next_x, y_to_check))
		{
			game->rays[i].horzhit_x = dda.next_x;
			game->rays[i].horzhit_y = dda.next_y;
			return (true);
		}
		dda.next_x += dda.x_step;
		dda.next_y += dda.y_step;
	}
	return (false);
}

static void	init_vertical_dda(t_game *game, t_dda *dda, int i)
{
	dda->x_intercept = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	if (game->rays[i].is_ray_facing_right)
		dda->x_intercept += TILE_SIZE;
	dda->y_intercept = game->player.y + (dda->x_intercept - game->player.x) * tan(game->rays[i].ray_angle);
	dda->x_step = TILE_SIZE;
	if (game->rays[i].is_ray_facing_left)
		dda->x_step *= -1;
	dda->y_step = TILE_SIZE * tan(game->rays[i].ray_angle);
	if (game->rays[i].is_ray_facing_up && dda->y_step > 0)
		dda->y_step *= -1;
	if (game->rays[i].is_ray_facing_down && dda->y_step < 0)
		dda->y_step *= -1;
	dda->next_x = dda->x_intercept;
	dda->next_y = dda->y_intercept;
}
static bool	find_vertocal_intersection(t_game *game, int i)
{
	t_dda	dda;
	
	initiatize_rayfacing(game, game->rays[i].ray_angle, i);
	init_vertical_dda(game, &dda, i);
	while (dda.next_x >= 0 && dda.next_x <= WINDOW_WIDTH
		&& dda.next_y >= 0 && dda.next_y <= WINDOW_HEIGHT)
	{
		float x_to_check = dda.next_x;
		if (game->rays[i].is_ray_facing_left)
    		x_to_check -= 1;
		if (hit_wall(game, x_to_check, dda.next_y))
		{
			game->rays[i].verthit_x = dda.next_x;
			game->rays[i].verthit_y = dda.next_y;
			return (true);	
		}
		dda.next_x += dda.x_step;
		dda.next_y += dda.y_step;
	}
	return (false);
}

void	cast_one_ray(t_game *game , int i)
{
	float horz_hit_distance;
	float vert_hit_distance;

	horz_hit_distance = 1e30;
    vert_hit_distance = 1e30;
	game->rays[i].ray_angle = normalize_angle(game->rays[i].ray_angle);
	if (find_horizontal_intersection(game, i)){
		horz_hit_distance = distance(game->player.x, game->player.y,
			game->rays[i].horzhit_x, game->rays[i].horzhit_y);
	}
	if (find_vertocal_intersection(game, i)){
		vert_hit_distance = distance(game->player.x, game->player.y,
			game->rays[i].verthit_x, game->rays[i].verthit_y);
	}
	store_final_hit(game, horz_hit_distance, vert_hit_distance, i);
}
