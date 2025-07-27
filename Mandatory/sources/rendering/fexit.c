/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:52:25 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/27 15:23:05 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	fexit(t_game *game)
{
	 cleanup_textures(game);
    if (game->img.img_ptr)
        mlx_destroy_image(game->mlx, game->img.img_ptr);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
	if (game->map.grid)
    free_grid(game->map.grid);
	if (game->asset_data.north_tex_path)
    	free(game->asset_data.north_tex_path);
	if (game->asset_data.south_tex_path)
    	free(game->asset_data.south_tex_path);
	if (game->asset_data.west_tex_path)
    	free(game->asset_data.west_tex_path);
	if (game->asset_data.east_tex_path)
    	free(game->asset_data.east_tex_path);
    exit(1);
}
