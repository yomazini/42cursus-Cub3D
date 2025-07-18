/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:40:57 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/18 19:53:12 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	validate_walls_are_closed(t_game *data)
{
	char	**map_copy;

	if (data->map.height > 200 && data->map.height > 200)
	{
		exit_with_error("the map too big", data);
	}
	map_copy = duplicate_grid(data->map.grid, data->map.height);
	if (!map_copy)
		exit_with_error("Malloc failed for map copy.", data);
	flood_fill_rec(data, map_copy,
		(int)data->map.map_player_y, (int)data->map.map_player_x);
	free_grid(map_copy);
}

static void	handle_identifier(char **tokens, t_game *data)
{
	if (!ft_strncmp(tokens[0], "NO", 3) || !ft_strncmp(tokens[0], "SO", 3)
		|| !ft_strncmp(tokens[0], "EA", 3) || !ft_strncmp(tokens[0], "WE", 3))
	{
		if (count_tokens(tokens) != 2)
			exit_with_error("Invalid texture format", data);
		parse_texture(tokens, data);
	}
	else if (!ft_strncmp(tokens[0], "F", 2) || !ft_strncmp(tokens[0], "C", 2))
		parse_color(tokens, data);
	else
		exit_with_error("Unknown identifier in the file", data);
}

void	parse_identifiers(t_list *id_lines, t_game *data)
{
	t_list	*current;
	char	**tokens;

	current = id_lines;
	while (current)
	{
		tokens = ft_split((char *)current->content, ' ');
		if (!tokens)
			exit_with_error("malloc failed here", data);
		if (count_tokens(tokens) < 2)
			exit_with_error("Invalid identifier format", data);
		handle_identifier(tokens, data);
		free_grid(tokens);
		current = current->next;
	}
	validate_all_identifiers_found(data);
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
	if (grid_copy[y][x] == '1' || grid_copy[y][x] == 'V')
		return ;
	grid_copy[y][x] = 'V';
	flood_fill_rec(data, grid_copy, y - 1, x);
	flood_fill_rec(data, grid_copy, y, x + 1);
	flood_fill_rec(data, grid_copy, y + 1, x);
	flood_fill_rec(data, grid_copy, y, x - 1);
}
