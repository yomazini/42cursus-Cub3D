/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:35:30 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/17 10:39:25 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

#include "../../includes/cub3D.h"

void	update_player(t_game *game)
{
	t_p	p;
	
	game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;
	game->player.rotation_angle = normalize_angle(game->player.rotation_angle);
	p.move_step = game->player.walk_direction * game->player.move_speed;
	p.move_x = cos(game->player.rotation_angle) * p.move_step;
	p.move_y = sin(game->player.rotation_angle) * p.move_step;
	p.strafe_angle = game->player.rotation_angle + (PI / 2);
    p.strafe_step = game->player.strafe_direction * game->player.move_speed;
    float strafe_x = cos(p.strafe_angle) * p.strafe_step;
    float strafe_y = sin(p.strafe_angle) * p.strafe_step;
	p.new_x = game->player.x + p.move_x + strafe_x;
    p.new_y = game->player.y + p.move_y + strafe_y;	
	if(!hit_wall(game, p.new_x, p.new_y))
		game->player.x = p.new_x;
	if(!hit_wall(game, p.new_x, p.new_y))
		game->player.y = p.new_y;
}

