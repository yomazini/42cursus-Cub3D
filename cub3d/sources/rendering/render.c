/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:42:51 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/14 11:31:16 by eel-garo         ###   ########.fr       */
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

	while (i < TILE_SIZE - 1)
	{
		j = 0;
		while (j < TILE_SIZE - 1)
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

	y = 0;
	while (y < game->map.height && game->map.grid[y])
	{
		x = 0;
		while (x < game->map.width && game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '1'){
				draw_square(game, x * TILE_SIZE, y * TILE_SIZE, 0x006272A4);
			}
			else{
				draw_square(game, x * TILE_SIZE, y * TILE_SIZE, 0xFFFFFFFF);
			}
			x++;
		}
		y++;	
	}
}

void draw_player(t_game *game)
{
	int i = -1;
	int j;

	while (i < 1)
	{
		j = -1;
		while (j < 1)
		{
			my_mlx_pixel_put(game, game->player.x + j, game->player.y + i, 0x006666FF);
			j++;
		}
		i++;
	}
}

void	render(t_game *game)
{
	draw_map(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}