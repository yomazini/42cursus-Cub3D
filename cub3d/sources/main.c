/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:23:58 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/18 19:44:14 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	print_parsed_data(t_game *data)
{
	int	i;

	printf("\n--- PARSING COMPLETE ---\n");
	printf("✅ Textures:\n");
	printf("   NO: %s\n", data->asset_data.north_tex_path);
	printf("   SO: %s\n", data->asset_data.south_tex_path);
	printf("   WE: %s\n", data->asset_data.west_tex_path);
	printf("   EA: %s\n", data->asset_data.east_tex_path);
	printf("✅ Floor Color:   R=%d, G=%d, B=%d\n", data->asset_data.floor_rgb.red,
		data->asset_data.floor_rgb.green, data->asset_data.floor_rgb.blue);
	printf("✅ Ceiling Color: R=%d, G=%d, B=%d\n", data->asset_data.ceilllig_rgb.red,
		data->asset_data.ceilllig_rgb.green, data->asset_data.ceilllig_rgb.blue);
	printf("\n--- MAP DATA ---\n");
	printf("Player Start: (x=%.1f, y=%.1f), Facing: %c\n", data->map.map_player_x,
		data->map.map_player_y, data->map.spawn_side_face);
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

float	rotation_angle(t_game *game)
{
	if (game->map.spawn_side_face == 'E')
		return (0);
	else if (game->map.spawn_side_face == 'N')
		return (1.5 * PI);
	else if (game->map.spawn_side_face == 'W')
		return (PI);
	else if (game->map.spawn_side_face == 'S')
		return (PI / 2);
	else
		return (-1);
}

bool	launch_game(t_game *game)
{
	game->player.x = game->map.map_player_x * TILE_SIZE;
	game->player.y = game->map.map_player_y * TILE_SIZE;
	game->player.rotation_angle = rotation_angle(game);
	game->player.turn_direction = 0;
	game->player.walk_direction = 0;
	game->player.strafe_direction = 0;
	game->player.move_speed = 3;
	game->player.rotation_speed = 1 * (PI / 180);
	intialize_mlx(game);
	return (true);
}

int	main(int ac, char **av)
{
	t_game	game;

	// if (WINDOW_HEIGHT != 720 || WINDOW_WIDTH != 1280)
	// 	return (1);
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
	free_grid(game.map.grid);
	free(game.asset_data.north_tex_path);
	free(game.asset_data.south_tex_path);
	free(game.asset_data.west_tex_path);
	free(game.asset_data.east_tex_path);
	return (0);
}
