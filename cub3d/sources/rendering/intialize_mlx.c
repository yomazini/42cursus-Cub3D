/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:31:10 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/14 11:21:42 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_exit(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	game_loop(t_game *game)
{
	render(game);
	
	return (0);
}

bool	intialize_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->img.img_ptr = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
		&game->img.line_len, &game->img.endian);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (false);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_loop(game->mlx);
	return (true);		
}
