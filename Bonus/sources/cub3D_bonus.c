/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:23:58 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/28 11:12:14 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	print_parsed_data(t_game *data)
{
	int	i;

	printf("\n--- PARSING BONUS COMPLETE ---\n");
	printf("✅ Textures:\n");
	printf("   NO: %s\n", data->asset_data.north_tex_path);
	printf("   SO: %s\n", data->asset_data.south_tex_path);
	printf("   WE: %s\n", data->asset_data.west_tex_path);
	printf("   EA: %s\n", data->asset_data.east_tex_path);
	printf("✅ Floor Color:   R=%d, G=%d, B=%d\n HEX=%d\n", data->asset_data.floor_rgb.red,
		data->asset_data.floor_rgb.green, data->asset_data.floor_rgb.blue, data->asset_data.floor_rgb.hex_color);
	printf("✅ Ceiling Color: R=%d, G=%d, B=%d\n HEX=%d\n", data->asset_data.ceilllig_rgb.red,
		data->asset_data.ceilllig_rgb.green, data->asset_data.ceilllig_rgb.blue, data->asset_data.ceilllig_rgb.hex_color);
	printf("\n--- MAP DATA ---\n");
	printf("Player Start: (x=%.1f, y=%.1f), Facing: %c\n", data->map.map_player_x,
		data->map.map_player_y, data->map.side_face);
	printf("Map Dimensions: Height=%d, Width=%d\n", data->map.height, data->map.width);
	printf("--- NORMALIZED MAP GRID ---\n");
	i = 0;
	while (data->map.grid && data->map.grid[i])
	{
		printf("%s|\n", data->map.grid[i]);
		i++;
	}
	printf("--------------------------\n\n");
}

void	run_parser(char *filename, t_game *game)
{
	t_list	*all_lines;
	t_list	*id_lines;
	t_list	*map_lines;

	if (validate_filename(filename) == 0)
		exit_with_error("Invalid file extension. Must be .cub", game);
	all_lines = read_file_to_list(filename);
	if (!all_lines)
		exit_with_error("File is empty or could not be read.", game);
	id_lines = NULL;
	map_lines = NULL;
	separate_file_content(all_lines, &id_lines, &map_lines);
	ft_lstclear(&all_lines, free);
	parse_identifiers(id_lines, game);
	ft_lstclear(&id_lines, free);
	create_map_grid(&map_lines, game);
	validate_map_content(game);
	normalize_map_grid(game);
	validate_walls_are_closed(game);
}

bool	launch_game(t_game *game)
{
	intialize_mlx(game);
	return (true);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3D <path_to_map.cub>\n", 2);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	run_parser(av[1], &game);
	print_parsed_data(&game);
	sleep(1);
	launch_game(&game);
	if (game.map.grid)
		free_grid(game.map.grid);
	if (game.asset_data.north_tex_path)
		free(game.asset_data.north_tex_path);
	if (game.asset_data.south_tex_path)
		free(game.asset_data.south_tex_path);
	if (game.asset_data.west_tex_path)
		free(game.asset_data.west_tex_path);
	if (game.asset_data.east_tex_path)
		free(game.asset_data.east_tex_path);
	return (0);
}
