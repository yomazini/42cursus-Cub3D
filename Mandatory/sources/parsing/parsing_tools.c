/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:56:36 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/18 17:09:21 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	count_char_in_string(const char *str, char c)
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

int	is_string_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_string_purely_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
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
