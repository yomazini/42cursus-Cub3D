/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put_minimap.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 08:00:27 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/27 09:00:23 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	my_mlx_pixel_put_minimap(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < MINIMAP_WIDTH_IN_PIXELS
		&& y >= 0 && y < MINIMAP_HEIGHT_IN_PIXELS)
	{
		my_mlx_pixel_put(game, x, y, color);
	}
}
