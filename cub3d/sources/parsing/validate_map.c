/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:24:09 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/18 17:09:13 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*reconstruct_color_string(char **tokens, int token_count)
{
	char	*result;
	char	*temp;
	int		i;
	int		total_len;

	total_len = 0;
	i = 0;
	while (++i < token_count)
		total_len += ft_strlen(tokens[i]) + 1;
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (++i < token_count)
	{
		if (i > 1)
		{
			temp = ft_strjoin(result, " ");
			free(result);
			result = temp;
			if (!result)
				return (NULL);
		}
		temp = ft_strjoin(result, tokens[i]);
		free(result);
		result = temp;
		if (!result)
			return (NULL);
	}
	return (result);
}

void	parse_color(char **tokens, t_game *data)
{
    char	*color_string;
    char	**rgb_untrimmed;
    char	*trimmed_val;
    int		rgb[3];
    int		i;
    int		token_count;

	token_count = count_tokens(tokens);
	if (token_count == 2)
	    color_string = ft_strdup(tokens[1]);
	else if (token_count > 2)
	    color_string = reconstruct_color_string(tokens, token_count);
	else
	    exit_with_error("Invalid color format: missing color values.", data);
	if (!color_string)
	    exit_with_error("Memory allocation failed.", data);
	if (count_char_in_string(color_string, ',') != 2)
	{
	    free(color_string);
	    exit_with_error("Invalid RGB format: must have exactly two commas.", data);
	}
	rgb_untrimmed = ft_split(color_string, ',');
	free(color_string);
	if (!rgb_untrimmed || count_tokens(rgb_untrimmed) != 3)
	{
	    free_grid(rgb_untrimmed);
	    exit_with_error("Invalid RGB format: must have three values.", data);
	}
	i = -1;
	while (++i < 3)
	{
	    trimmed_val = ft_strtrim(rgb_untrimmed[i], " \t");
	    if (!trimmed_val)
	    {
	        free_grid(rgb_untrimmed);
	        exit_with_error("Memory allocation failed.", data);
	    }
	    if (!is_string_purely_numeric(trimmed_val))
	    {
	        (free(trimmed_val), free_grid(rgb_untrimmed));
	        exit_with_error("RGB values must be numeric.", data);
	    }
	    rgb[i] = ft_atoi(trimmed_val);
	    if (rgb[i] < 0 || rgb[i] > 255)
	    {
	        (free(trimmed_val), free_grid(rgb_untrimmed));
	        exit_with_error("RGB color value out of range (0-255).", data);
	    }
	    free(trimmed_val);
	}
	free_grid(rgb_untrimmed);
	if (ft_strncmp("F", tokens[0], 2) == 0)
	{
	    if (data->checklist.f == 1) 
	        exit_with_error("Duplicate F identifier.", data);
	    data->checklist.f = 1;
	    data->asset_data.floor_rgb = (t_rgb){rgb[0], rgb[1], rgb[2], 1};
	}
	else if (ft_strncmp("C", tokens[0], 2) == 0)
	{
		if (data->checklist.c == 1) 
		    exit_with_error("Duplicate C identifier.", data);
		data->checklist.c = 1;
		data->asset_data.ceilllig_rgb = (t_rgb){rgb[0], rgb[1], rgb[2], 1};
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
		return ;
	grid_copy[y][x] = 'F';
	flood_fill_rec(data, grid_copy, y - 1, x);
	flood_fill_rec(data, grid_copy, y + 1, x);
	flood_fill_rec(data, grid_copy, y, x + 1);
	flood_fill_rec(data, grid_copy, y, x - 1);
}
