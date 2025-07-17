/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:42:51 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/17 13:52:47 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
			else if (game->map.grid[y][x] == '0')
				color = 0xFFFFFFFF;
			else if (game->map.grid[y][x] == ' ')
				color = 0x710000;
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
	render_3d_projaction(game);
	draw_map(game);
	draw_player(game);
	draw_minimap_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}
