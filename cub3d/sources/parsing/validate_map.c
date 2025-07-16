/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:24:09 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/15 21:11:33 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	parse_identifiers(t_list *id_lines, t_game *data)
{
	t_list	*current;
	char	**tokens;

	current = id_lines;
	while (current)
	{
		tokens = ft_split((char *)current->content ,' ');
		if (!tokens)
			exit_with_error("malloc failed here", data);
		if (count_tokens(tokens) != 2)
			return ;
//			exit(1);
//			exit_with_error("error in the number of tokens ", data);
		if (!ft_strncmp(tokens[0], "NO", 3) || !ft_strncmp(tokens[0], "SO", 3)
			|| !ft_strncmp(tokens[0], "EA", 3) || !ft_strncmp(tokens[0], "WE", 3))
			parse_texture(tokens,data);
		else if (!ft_strncmp(tokens[0], "F", 2) || !ft_strncmp(tokens[0], "C", 2))
			printf("\n\n\n\n\n\n\nenter the parse color fun\n");
			// parse_color(tokens,data);
		else
			exit_with_error("Unkown identifire in the file",data);		
		free_grid(tokens);
		current = current->next;
	}
	validate_all_identifiers_found(data);
}

void	parse_color(char **tokens, t_game *data)
{
	char	**rgb_values;
	t_rgb	*color_strcut;
	int		r;
	int		g;
	int		b;
	printf("\nenter the parse color fun\n");
	rgb_values = ft_split(tokens[1], ',');
	if (!rgb_values || count_tokens(rgb_values) != 3)
		exit_with_error("problem in RGB file", data);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_with_error("RGB color value out of range 0 - 255", data);
	if (ft_strncmp("F", tokens[0], 2) == 0)
	{
		if (data->checklist.f == 1)
			exit_with_error("Duplication in the identifiesrs F C ", data);
		data->checklist.f = 1;
		data->asset_data.floor_rgb.red = r;
		data->asset_data.floor_rgb.blue = b;
		data->asset_data.floor_rgb.green = g;
		data->asset_data.floor_rgb.is_set = 1;
	}
	if (ft_strncmp("C", tokens[0], 2) == 0)
	{
		if (data->checklist.c == 1)		
			exit_with_error("Duplication in the identifiesrs F C ", data);
		data->checklist.c = 1;
		data->asset_data.ceilllig_rgb.red = r;
		data->asset_data.ceilllig_rgb.blue = b;
		data->asset_data.ceilllig_rgb.green = g;
		data->asset_data.ceilllig_rgb.is_set = 1;
	}
	free_grid(rgb_values);
}

void	validate_all_identifiers_found(t_game *data)
{
	if (!data->checklist.c || !data->checklist.f 
		|| !data->checklist.we || !data->checklist.ea
		|| !data->checklist.no || !data->checklist.so
	)
		exit_with_error("the Identifier are not competed check them", data);	
}
