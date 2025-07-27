/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:46:37 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/18 17:09:18 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

void	create_map_grid(t_list **map_lines_head, t_game *data)
{
	t_list	*current;
	int		i;

	i = 0;
	data->map.height = ft_lstsize(*map_lines_head);
	if (data->map.height == 0)
	{
		exit_with_error("map is empty", data);
	}
	data->map.grid = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.grid)
		exit_with_error("the allocation in create_map_grid failed", data);
	current = *map_lines_head;
	while (current)
	{
		data->map.grid[i] = ft_strdup((char *)current->content);
		if (!data->map.grid[i])
			exit_with_error("grid allocation failed", data);
		current = current->next;
		i++;
	}
	data->map.grid[i] = NULL;
	ft_lstclear(map_lines_head, free);
}

static void	validate_tile(t_game *data, char c, int x, int y)
{
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
}

void	validate_map_content(t_game *data)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	data->map.player_count = 0;
	while (data->map.grid[++y])
	{
		x = -1;
		while (data->map.grid[y][++x])
		{
			c = data->map.grid[y][x];
			validate_tile(data, c, x, y);
		}
	}
	if (data->map.player_count != 1)
		exit_with_error("Map must have exactly one start position.", data);
}
