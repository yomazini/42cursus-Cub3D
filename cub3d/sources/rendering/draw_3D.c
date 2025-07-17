/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:19:07 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/17 11:20:03 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	render_3d(t_game *game, int wall_top_pixel, int wall_bottom_pixel, int i)
{
	int	y;

	y = 0;
	while (y < wall_top_pixel)
		my_mlx_pixel_put(game, i, y++, 0x0087CEEB);
	y = wall_top_pixel;
	while (y < wall_bottom_pixel)
		my_mlx_pixel_put(game, i, y++,0x00A9A9A9);
	y = wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
		my_mlx_pixel_put(game, i, y++, 0xc29b3e);
}

/**
  	X  = ? (Projection wall height)
	1- Using Triangle Similarity:
		A/B = D/C
		D = X
		A = actuial wall height = TILE_SIZE
		B = distance to wall = ray distance (from raycasting)
		C = distance from player to proj.plane = (WINDOW_WIDTH / 2) / tan(FOV / 2)
		D = A/B * C   
*/

void	render_3d_projaction(t_game *game)
{
	t_3d	t;
	int		i;

	t.dist_to_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		t.corrected_dist = game->rays[i].distance
			* cos(game->rays[i].ray_angle - game->player.rotation_angle);
				
		t.projected_wall_height = (TILE_SIZE / t.corrected_dist) * t.dist_to_proj_plane;
		
		t.wall_top_pixel = (WINDOW_HEIGHT / 2) - (t.projected_wall_height / 2);
		if (t.wall_top_pixel < 0)
			t.wall_top_pixel = 0;
		t.wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (t.projected_wall_height / 2);
		if (t.wall_bottom_pixel > WINDOW_HEIGHT)
			t.wall_bottom_pixel = WINDOW_HEIGHT;
		render_3d(game, t.wall_top_pixel, t.wall_bottom_pixel, i);
		i++;
	}	
}
