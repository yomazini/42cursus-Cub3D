/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:01:10 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/27 14:01:37 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

void	cleanup_textures(t_game *game)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (game->asset_data.textures[i].img_ptr)
			mlx_destroy_image(game->mlx, game->asset_data.textures[i].img_ptr);
		i++;
	}
}
