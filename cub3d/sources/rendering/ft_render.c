/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:42:51 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/16 14:45:36 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char *dest;

	dest = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
	*(unsigned int *)dest = color;
} 

void draw_square(t_game *game, int x, int y, int color)
{
	int i = 0;
	int j;
	int	minimap_tile_size;

	minimap_tile_size = TILE_SIZE * MINIMAP_SCALE_FACTOR;
	while (i < minimap_tile_size - 1)
	{
		j = 0;
		while (j < minimap_tile_size - 1)
		{
			my_mlx_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}	
}

void	draw_map(t_game *game)
{
	int	x,y;
	int minimap_x, minimap_y;
	int color;
	

	y = 0;
	while (y < game->map.height && game->map.grid[y])
	{
		x = 0;
		while (x < game->map.width && game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '1')
				color = 0x37CACEFF;
			else
				color = 0xFFFFFFFF;
			minimap_x = (x * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
			minimap_y = (y * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
			draw_square(game, minimap_x, minimap_y, color);
			x++;
		}
		y++;	
	}
}

void draw_player(t_game *game)
{
	int y = -1;
	int x;
	int	player_minimap_x;
	int	player_minimap_y;

	player_minimap_x = game->player.x * MINIMAP_SCALE_FACTOR;
	player_minimap_y = game->player.y * MINIMAP_SCALE_FACTOR;
	while (y < 1)
	{
		x = -1;
		while (x < 1)
		{
			my_mlx_pixel_put(game, player_minimap_x + x, player_minimap_y + y, 0x006666FF);
			x++;
		}
		y++;
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

void	render_3d(t_game *game, int wall_top_pixel, int wall_bottom_pixel, int i)
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

void	render_3dproj(t_game *game)
{
	int	i;
	float	dist_to_proj_plane;
	float	projected_wall_height;
	float	corrected_dist;

	int		wall_top_pixel;
	int		wall_bottom_pixel;

	dist_to_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		corrected_dist = game->rays[i].distance
			* cos(game->rays[i].ray_angle - game->player.rotation_angle);
				
		projected_wall_height = (TILE_SIZE / corrected_dist) * dist_to_proj_plane;
		
		wall_top_pixel = (WINDOW_HEIGHT / 2) - (projected_wall_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (projected_wall_height / 2);
		if (wall_bottom_pixel > WINDOW_HEIGHT)
			wall_bottom_pixel = WINDOW_HEIGHT;
		render_3d(game, wall_top_pixel, wall_bottom_pixel, i);
		i++;
	}	
}


void draw_minimap_rays(t_game *game)
{
    int i = 0;
    while (i < WINDOW_WIDTH)
    {
        draw_line(
            game,
            game->player.x * MINIMAP_SCALE_FACTOR,
            game->player.y * MINIMAP_SCALE_FACTOR,
            game->rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR,
            game->rays[i].wall_hit_y * MINIMAP_SCALE_FACTOR
        );
        i++;
    }
}

void	ft_render(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	update_player(game);
	cast_rays(game);
	render_3dproj(game);
	draw_map(game);
	draw_player(game);
	draw_minimap_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}