/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:19:07 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/27 08:50:29 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
		t.projected_wall_height = (TILE_SIZE / t.corrected_dist)
			* t.dist_to_proj_plane;
		t.wall_top_pixel = (WINDOW_HEIGHT / 2)
			- (t.projected_wall_height / 2);
		if (t.wall_top_pixel < 0)
			t.wall_top_pixel = 0;
		t.wall_bottom_pixel = (WINDOW_HEIGHT / 2)
			+ (t.projected_wall_height / 2);
		if (t.wall_bottom_pixel > WINDOW_HEIGHT)
			t.wall_bottom_pixel = WINDOW_HEIGHT;
		render_3d(game, &t, i);
		i++;
	}
}
