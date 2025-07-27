/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:14:57 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/27 10:39:17 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

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
