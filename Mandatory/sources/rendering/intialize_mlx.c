/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:31:10 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/27 12:49:44 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	game_loop(t_game *game)
{
	ft_render(game);
	return (0);
}

static int	key_press_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		fexit(game);
	if (keycode == KEY_W)
		game->player.walk_direction = +1;
	if (keycode == KEY_S)
		game->player.walk_direction = -1;
	if (keycode == KEY_D)
		game->player.strafe_direction = +1;
	if (keycode == KEY_A)
		game->player.strafe_direction = -1;
	if (keycode == KEY_RIGHT)
		game->player.turn_direction = +1;
	if (keycode == KEY_LEFT)
		game->player.turn_direction = -1;
	return (0);
}

static int	key_release_hook(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S)
		game->player.walk_direction = 0;
	if (keycode == KEY_A || keycode == KEY_D)
		game->player.strafe_direction = 0;
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		game->player.turn_direction = 0;
	return (0);
}

static void	init(t_game *game)
{
	game->player.x = game->map.map_player_x * TILE_SIZE;
	game->player.y = game->map.map_player_y * TILE_SIZE;
	game->player.rotation_angle = rotation_angle(game);
	game->player.turn_direction = 0;
	game->player.walk_direction = 0;
	game->player.strafe_direction = 0;
	game->player.move_speed = 5;
	game->player.rotation_speed = 2 * (PI / 180);
}

bool	intialize_mlx(t_game *game)
{
	init(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->img.img_ptr = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (false);
	load_textures(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->win, 17, 0, fexit, game);
	mlx_hook(game->win, 2, 1L << 0, key_press_hook, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_hook, game);
	mlx_loop(game->mlx);
	return (true);
}
