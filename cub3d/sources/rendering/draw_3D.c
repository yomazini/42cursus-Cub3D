/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:19:07 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/26 14:42:48 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static t_texture	*get_wall_texture(t_game *game, int i)
{
	t_ray	*ray;

	ray = &game->rays[i];
	if (ray->was_hit_vertical)
	{
		if (ray->is_ray_facing_right)
			return (&game->asset_data.textures[WEST]);
		else
			return (&game->asset_data.textures[EAST]);
	}
	else
	{
		if (ray->is_ray_facing_down)
			return (&game->asset_data.textures[NORTH]);
		else
			return (&game->asset_data.textures[SOUTH]);
	}
}

static void	draw_wall_stripe(t_game *game, t_3d *t, int i)
{
	t_texture	*tex;
	int			tex_x;
	int			tex_y;
	int			color;
	float		y_step;
	float		tex_pos;

	tex = get_wall_texture(game, i);
	
	if (game->rays[i].was_hit_vertical)
		tex_x = fmod(game->rays[i].wall_hit_y, TILE_SIZE);
	else
		tex_x = fmod(game->rays[i].wall_hit_x, TILE_SIZE);
	tex_x = tex_x * ((float)tex->width / TILE_SIZE);
	y_step = (float)tex->height / t->projected_wall_height;
	tex_pos = 0; 
	if (t->projected_wall_height > WINDOW_HEIGHT)
		tex_pos = ((t->projected_wall_height - WINDOW_HEIGHT) / 2.0) * y_step;
	for (int y = t->wall_top_pixel; y < t->wall_bottom_pixel; y++)
	{
		tex_y = (int)tex_pos;
		if (tex_x < 0) tex_x = 0;
		if (tex_x >= tex->width) tex_x = tex->width - 1;
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= tex->height) tex_y = tex->height - 1;
		color = *(unsigned int *)(tex->addr + (tex_y * tex->line_len
					+ tex_x * (tex->bpp / 8)));
		my_mlx_pixel_put(game, i, y, color);
		tex_pos += y_step;
	}
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

void	render_3d(t_game *game, t_3d *t, int i)
{
	int	y;

	y = 0;
	while (y < t->wall_top_pixel)
	{
		my_mlx_pixel_put(game, i, y, game->asset_data.ceilllig_rgb.hex_color);
		y++;
	}
	draw_wall_stripe(game, t, i);
	y = t->wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(game, i, y, game->asset_data.floor_rgb.hex_color);	
		y++;
	}
}

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


