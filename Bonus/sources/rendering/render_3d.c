/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 08:47:49 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/27 12:57:31 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

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

static void	init_strip_cord(t_game *game, t_ws *ws, int i, t_texture *tex)
{
	if (game->rays[i].was_hit_vertical)
		ws->tex_x = fmod(game->rays[i].wall_hit_y, TILE_SIZE);
	else
		ws->tex_x = fmod(game->rays[i].wall_hit_x, TILE_SIZE);
	ws->tex_x = ws->tex_x * ((float)tex->width / TILE_SIZE);
}

static void	boundaries(t_ws *ws, t_texture *tex)
{
	if (ws->tex_x < 0)
		ws->tex_x = 0;
	if (ws->tex_x >= tex->width)
		ws->tex_x = tex->width - 1;
	if (ws->tex_y < 0)
		ws->tex_y = 0;
	if (ws->tex_y >= tex->height)
		ws->tex_y = tex->height - 1;
}

static void	draw_wall_stripe(t_game *game, t_3d *t, int i)
{
	t_texture	*tex;
	t_ws		ws;
	int			y;

	tex = get_wall_texture(game, i);
	init_strip_cord(game, &ws, i, tex);
	ws.y_step = (float)tex->height / t->projected_wall_height;
	ws.tex_pos = 0;
	if (t->projected_wall_height > WINDOW_HEIGHT)
		ws.tex_pos = ((t->projected_wall_height - WINDOW_HEIGHT) / 2.0)
			* ws.y_step;
	y = t->wall_top_pixel;
	while (y < t->wall_bottom_pixel)
	{
		ws.tex_y = (int)ws.tex_pos;
		boundaries(&ws, tex);
		ws.color = *(unsigned int *)(tex->addr + (ws.tex_y * tex->line_len
					+ ws.tex_x * (tex->bpp / 8)));
		my_mlx_pixel_put(game, i, y, ws.color);
		ws.tex_pos += ws.y_step;
		y++;
	}
}

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
