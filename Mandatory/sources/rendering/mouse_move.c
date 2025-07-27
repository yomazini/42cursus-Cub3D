/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:51:25 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/27 11:28:23 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	float	diffrence;

	(void)y;
	center_x = WINDOW_WIDTH / 2;
	diffrence = (float)(x - center_x);
	game->player.rotation_angle += diffrence * MOUSE_SENSITIVITY;
	game->player.rotation_angle = normalize_angle(game->player.rotation_angle);
	mlx_mouse_move(game->win, center_x, (WINDOW_HEIGHT / 2));
	return (0);
}
