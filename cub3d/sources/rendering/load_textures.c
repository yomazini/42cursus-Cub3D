/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:28:42 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/27 08:59:58 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	load_one_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
		exit_with_error("Failed to load texture", game);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		exit_with_error("Failed to get texture data addr", game);
}

void	load_textures(t_game *game)
{
	load_one_texture(game, &game->asset_data.textures[NORTH],
		game->asset_data.north_tex_path);
	load_one_texture(game, &game->asset_data.textures[SOUTH],
		game->asset_data.south_tex_path);
	load_one_texture(game, &game->asset_data.textures[WEST],
		game->asset_data.west_tex_path);
	load_one_texture(game, &game->asset_data.textures[EAST],
		game->asset_data.east_tex_path);
}
