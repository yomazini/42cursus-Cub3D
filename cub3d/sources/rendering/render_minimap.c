/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 07:53:33 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/25 10:49:31 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void draw_player(t_game *game)
{
	int y = -1;
	int x;
	while (y < 1)
	{
		x = -1;
		while (x < 1)
		{
			my_mlx_pixel_put(game, MINIMAP_CENTER_X + x, MINIMAP_CENTER_Y + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

typedef struct s_minimap_scale
{	
	int		mx;
	int		my;
	float	scale;
	float	world_x;
	float	world_y;
	int		grid_x;
	int		grid_y;	
}	t_mini;


void	render_loop(t_game *game, t_mini *m)
{
	m->world_x = game->player.x + ((m->mx - MINIMAP_CENTER_X) * m->scale);
	m->world_y = game->player.y + ((m->my - MINIMAP_CENTER_Y) * m->scale);
	m->grid_x = (int)(m->world_x / TILE_SIZE);
	m->grid_y = (int)(m->world_y / TILE_SIZE);
	if (fmod(m->world_x, TILE_SIZE) < m->scale || fmod(m->world_y, TILE_SIZE) < m->scale)
		my_mlx_pixel_put_minimap(game, m->mx, m->my, 0x00000000);
	else if (m->grid_y >= 0 && m->grid_y < game->map.height && m->grid_x >= 0
	&& m->grid_x < game->map.width && game->map.grid[m->grid_y][m->grid_x] != ' ')
	{
		if (game->map.grid[m->grid_y][m->grid_x] == '1')
			my_mlx_pixel_put_minimap(game, m->mx, m->my, 0x37CACEFF);
		else
			my_mlx_pixel_put_minimap(game, m->mx, m->my, 0xFFFFFFFF);
	}
	else
		my_mlx_pixel_put_minimap(game, m->mx, m->my, 0x000000);
}

void	render_minimap(t_game *game)
{
	t_mini m;
	
	m.scale = (MINIMAP_VIEW_RADIUS_IN_TILES * 2.0 * TILE_SIZE)
		/ (float)MINIMAP_WIDTH_IN_PIXELS;

	m.my = 0;
	while (m.my < MINIMAP_HEIGHT_IN_PIXELS)
	{
		m.mx = 0;
		while (m.mx < MINIMAP_WIDTH_IN_PIXELS)
		{
			render_loop(game, &m);
			m.mx++;		
		}
		m.my++;	
	}
	draw_player(game);	
}

