/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:24:09 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/18 18:10:15 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static char	*get_color_string(char **tokens, int token_count, t_game *data)
{
	char	*color_string;

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
		exit_with_error("Invalid RGB format:two commas.", data);
	}
	return (color_string);
}

static void	validate_rgb_value(char *val, t_rgb_validator *validator)
{
	if (!is_string_purely_numeric(val))
	{
		(free(val), free_grid(validator->rgb_untrimmed));
		exit_with_error("RGB values must be numeric.", validator->data);
	}
	validator->rgb[validator->i] = ft_atoi(val);
	if (validator->rgb[validator->i] < 0 || validator->rgb[validator->i] > 255)
	{
		(free(val), free_grid(validator->rgb_untrimmed));
		exit_with_error("RGB out of range (0-255).", validator->data);
	}
}

static void	parse_rgb_values(char **rgb_untrimmed, int *rgb, t_game *data)
{
	char			*trimmed_val;
	t_rgb_validator	validator;
	int				i;

	validator.rgb_untrimmed = rgb_untrimmed;
	validator.rgb = rgb;
	validator.data = data;
	i = -1;
	while (++i < 3)
	{
		validator.i = i;
		trimmed_val = ft_strtrim(rgb_untrimmed[i], " \t");
		if (!trimmed_val)
		{
			free_grid(rgb_untrimmed);
			exit_with_error("Memory allocation failed.", data);
		}
		validate_rgb_value(trimmed_val, &validator);
		free(trimmed_val);
	}
}

static void	assign_color_to_data(char **tokens, int *rgb, t_game *data)
{
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

void	parse_color(char **tokens, t_game *data)
{
	char	*color_string;
	char	**rgb_untrimmed;
	int		rgb[3];
	int		token_count;

	token_count = count_tokens(tokens);
	color_string = get_color_string(tokens, token_count, data);
	rgb_untrimmed = ft_split(color_string, ',');
	free(color_string);
	if (!rgb_untrimmed || count_tokens(rgb_untrimmed) != 3)
	{
		free_grid(rgb_untrimmed);
		exit_with_error("Invalid RGB format: must have three values.", data);
	}
	parse_rgb_values(rgb_untrimmed, rgb, data);
	free_grid(rgb_untrimmed);
	assign_color_to_data(tokens, rgb, data);
}
