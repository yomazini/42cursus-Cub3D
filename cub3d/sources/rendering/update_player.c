/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:35:30 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/16 12:31:10 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	update_player(t_game *game)
{
	float	move_step;
	float	move_x;
	float	move_y;
	float	new_x;
	float	new_y;
	float   strafe_angle;
	float   strafe_step;
	
	game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;
	game->player.rotation_angle = normalize_angle(game->player.rotation_angle);
	
	move_step = game->player.walk_direction * game->player.move_speed;
	move_x = cos(game->player.rotation_angle) * move_step;
	move_y = sin(game->player.rotation_angle) * move_step;

	strafe_angle = game->player.rotation_angle + (PI / 2);
    strafe_step = game->player.strafe_direction * game->player.move_speed;
    float strafe_x = cos(strafe_angle) * strafe_step;
    float strafe_y = sin(strafe_angle) * strafe_step;
	
	 new_x = game->player.x + move_x + strafe_x;
    new_y = game->player.y + move_y + strafe_y;
	
	if(!hit_wall(game, new_x, new_y))
		game->player.x = new_x;
	if(!hit_wall(game, new_x, new_y))
		game->player.y = new_y;
}
