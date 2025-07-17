/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:23:58 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/17 14:47:29 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	parse_texture(char **tokens, t_game *data)
{
	char	*id;
	char	*path;
	int		fd;

	id = tokens[0];
	path = tokens[1];
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_with_error("fd prln", data);
	// printf("%s\n%i\n\n\n\n",path,fd);

		// TODO: Exit WITH ERROR
	close(fd);
	if (ft_strncmp("NO", id, 3) == 0)
	{
		if (data->checklist.no == 1)
			exit_with_error("duplication of Identifier in map ",data);
		data->checklist.no = 1;
		data->asset_data.north_tex_path = ft_strdup(path);
		// if (!data->asset_data.north_tex_path)
			// here free the prev and then call exit_with_error and return && return (NULL);
	}
	if (ft_strncmp("SO", id, 3) == 0)
	{
		if (data->checklist.so == 1)
			exit_with_error("duplication of Identifier in map ", data);
		data->checklist.so = 1;
		data->asset_data.south_tex_path = ft_strdup(path);
		// TODO: PROTET the dup if faild malloc			
	}
	if (ft_strncmp("WE", id, 3) == 0)
	{
		if (data->checklist.we == 1)
			exit_with_error("duplication of Identifier in map", data);
		data->checklist.we = 1;
		data->asset_data.west_tex_path = ft_strdup(path);
		// TODO: protect her 
	}
	if (ft_strncmp("EA", id, 3) == 0)
	{
		if (data->checklist.ea == 1)
			exit_with_error("duplication of Identifier in map ", data);
		data->checklist.ea = 1;
		data->asset_data.east_tex_path = ft_strdup(path);
		// TODO: protect her 
	}
}

static int	count_char_in_string(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}


static int	is_string_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if ( str[i] != ' ' && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
// EDITED VERSION; 
void	parse_color(char **tokens, t_game *data)
{
	char	**rgb_values;
	int		r;
	int		g;
	int		b;

	if (count_char_in_string(tokens[1], ',') != 2)
		exit_with_error("Invalid RGB format: must have exactly two commas.", data);

	rgb_values = ft_split(tokens[1], ',');
	if (!rgb_values || count_tokens(rgb_values) != 3)
	{
		free_grid(rgb_values);
		exit_with_error("Invalid RGB format: must have three color values.", data);
	}
	
	if (!is_string_numeric(rgb_values[0]) || \
		!is_string_numeric(rgb_values[1]) || \
		!is_string_numeric(rgb_values[2]))
	{
		free_grid(rgb_values);
		exit_with_error("RGB values must be numeric.", data);
	}
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	free_grid(rgb_values);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_with_error("RGB color value out of range (0-255).", data);
	if (ft_strncmp("F", tokens[0], 2) == 0)
	{
		if (data->checklist.f == 1)
			exit_with_error("Duplicate F identifier found.", data);
		data->checklist.f = 1;
		data->asset_data.floor_rgb = (t_rgb){r, g, b, 1};
	}
	else if (ft_strncmp("C", tokens[0], 2) == 0)
	{
		if (data->checklist.c == 1)
			exit_with_error("Duplicate C identifier found.", data);
		data->checklist.c = 1;
		data->asset_data.ceilllig_rgb = (t_rgb){r, g, b, 1};
	}
}


void	flood_fill_rec(t_game *data, char **grid_copy, int y, int x)
{
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width)
	{
		free_grid(grid_copy);
		exit_with_error("Map is not closed at the edges.", data);
	}
    if (grid_copy[y][x] == ' ')
    {
		free_grid(grid_copy);
		exit_with_error("Map has a hole; floor is adjacent to a space.", data);
	}
	if (grid_copy[y][x] == '1' || grid_copy[y][x] == 'F')
		return;
	grid_copy[y][x] = 'F';
	flood_fill_rec(data, grid_copy, y - 1, x);
	flood_fill_rec(data, grid_copy, y + 1, x);
	flood_fill_rec(data, grid_copy, y, x + 1);
	flood_fill_rec(data, grid_copy, y, x - 1);
}

char	**duplicate_grid(char **grid, int height)
{
	char	**new_grid;
	int		y;

	new_grid = malloc(sizeof(char *) * (height + 1));
	if (!new_grid)
		return (NULL);
	y = 0;
	while (y < height)
	{
		new_grid[y] = ft_strdup(grid[y]);
		if (!new_grid[y])
		{
			free_grid(new_grid);
			return (NULL);
		}
		y++;
	}
	new_grid[y] = NULL;
	return (new_grid);
}

void    validate_walls_are_closed(t_game *data)
{
	char	**map_copy;

	map_copy = duplicate_grid(data->map.grid, data->map.height);
	if (!map_copy)
		exit_with_error("Malloc failed for map copy.", data);
	flood_fill_rec(data, map_copy,
		(int)data->map.map_player_y, (int)data->map.map_player_x);
	free_grid(map_copy);
}

int	get_max_width(char **grid)
{
	int	i;
	int	max_width;

	max_width = 0; 
	i = 0;
	while (grid[i])
	{
		if (ft_strlen(grid[i]) > max_width)
			max_width = ft_strlen(grid[i]);	
		i++;
	}
	return (max_width);
}

void	normalize_map_grid(t_game *data)
{
	char	**new_grid;
	int		y;

	data->map.width = get_max_width(data->map.grid);
	if (data->map.width == 0)
		exit_with_error("Map content is invalid or empty.", data);
	new_grid = malloc(sizeof(char *) * (data->map.height + 1));
	if (!new_grid)
		exit_with_error("Malloc failed for new grid.", data);
	y = 0;
	while (y < data->map.height)
	{
		new_grid[y] = malloc(sizeof(char) * (data->map.width + 1));
		if (!new_grid[y])
			exit_with_error("Malloc failed for new grid row.", data);
		ft_memset(new_grid[y], ' ', data->map.width);
		ft_memcpy(new_grid[y], data->map.grid[y], ft_strlen(data->map.grid[y]));
		new_grid[y][data->map.width] = '\0';
		y++;
	}
	new_grid[y] = NULL;
	free_grid(data->map.grid);
	data->map.grid = new_grid;
}


void	validate_map_content(t_game *data)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	data->map.player_count = 0;
	while (data->map.grid[y])
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			c = data->map.grid[y][x];
			if (!ft_strchr("01NSWE ", c))
				exit_with_error("Invalid character in map.", data);
			if (ft_strchr("NSWE", c))
			{
				data->map.player_count++;
				data->map.map_player_x = (double)x + 0.5;
				data->map.map_player_y = (double)y + 0.5;
				data->map.spawn_side_face = c;
				data->map.grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (data->map.player_count != 1)
		exit_with_error("Map must have exactly one start position.", data);
}


void	create_map_grid(t_list **map_lines_head, t_game *data)
{
	t_list *current; 
	int i = 0;
	
	data->map.height = ft_lstsize(*map_lines_head);
	if (data->map.height == 0)
	{
		exit_with_error("map is empty",data);
	}
	data->map.grid = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.grid)
		exit_with_error("the allocation in create_map_grid failed",data);
	current = *map_lines_head;
	while (current)
	{
		data->map.grid[i] = ft_strdup((char *)current->content);
		if (!data->map.grid[i])
			exit_with_error("grid allocation failed",data);
		current = current->next;
		i++;
	}
	data->map.grid[i] = NULL;
	ft_lstclear(map_lines_head,free);
}

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
		printf("%s\n", data->map.grid[i]);
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
	if(game->map.spawn_side_face == 'E')
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
