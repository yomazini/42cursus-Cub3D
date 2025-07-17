/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:14:57 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/17 11:13:55 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


/**
 * I- cast_rays:
 
    1- get the ray angle (where the casting of rays start), ray_angle = player angle of rotation
	   half of his field of vie 
	2- number of rays to cast = the width of he window 
	3- whil we have rays to cast -> cast one ray -> move to the next ray by moving the ray_angle
	  to the next ray
	
	II- cast_one_ray
		1- find horizental hill to wall
			
	
*/

void	cast_rays(t_game *game)
{
	float	ray_angle;
	int		num_rays;
	int		i;

	ray_angle = game->player.rotation_angle - (FOV / 2);
	num_rays = WINDOW_WIDTH;
	i = 0;
	while (i < num_rays)
	{
		game->rays[i].ray_angle = ray_angle; 
		cast_one_ray(game, i);
		ray_angle += FOV / num_rays;
		i++;
	}	
}
