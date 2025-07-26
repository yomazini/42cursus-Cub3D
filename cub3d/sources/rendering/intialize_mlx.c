/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:31:10 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/26 13:12:05 by eel-garo         ###   ########.fr       */
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
	ft_render(game);
	return (0);
}
int	key_press_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
        ft_exit(game);
    if (keycode == KEY_UP)
        game->player.walk_direction = +1;
    if (keycode == KEY_DOWN)
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

int key_release_hook(int keycode, t_game *game)
{
    if (keycode == KEY_UP || keycode == KEY_DOWN)
        game->player.walk_direction = 0;
    if (keycode == KEY_A || keycode == KEY_D)
        game->player.strafe_direction = 0;
    if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
        game->player.turn_direction = 0;
    return (0);
}

static float	rotation_angle(t_game *game)
{
	if (game->map.spawn_side_face == 'E')
		return (0);
	else if (game->map.spawn_side_face == 'N')
		return (1.5 * PI);
	else if (game->map.spawn_side_face == 'W')
		return (PI);
	else if (game->map.spawn_side_face == 'S')
		return (PI / 2);
	else
		return (-1);
}

bool	intialize_mlx(t_game *game)
{
	game->player.x = game->map.map_player_x * TILE_SIZE;
	game->player.y = game->map.map_player_y * TILE_SIZE;
	game->player.rotation_angle = rotation_angle(game);
	game->player.turn_direction = 0;
	game->player.walk_direction = 0;
	game->player.strafe_direction = 0;
	game->player.move_speed = 5;
	game->player.rotation_speed = 2 * (PI / 180);
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
	mlx_hook(game->win, 17, 0, ft_exit, game);
	 mlx_hook(game->win, 2, 1L<<0, key_press_hook, game);
    mlx_hook(game->win, 3, 1L<<1, key_release_hook, game);
	mlx_loop(game->mlx);
	return (true);		
}
