/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_identifiers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:24:06 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/18 17:09:26 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//TODO: MUST PROTECT ALL strdups

static void	assign_texture_north_south(t_game *data, char *id, char *path)
{
	if (ft_strncmp("NO", id, 3) == 0)
	{
		if (data->checklist.no == 1)
			exit_with_error("Dup Id in map", data);
		data->checklist.no = 1;
		data->asset_data.north_tex_path = ft_strdup(path);
	}
	else if (ft_strncmp("SO", id, 3) == 0)
	{
		if (data->checklist.so == 1)
			exit_with_error("Dup Id in map", data);
		data->checklist.so = 1;
		data->asset_data.south_tex_path = ft_strdup(path);
	}
}

static void	assign_texture_path(t_game *data, char *id, char *path)
{
	if (ft_strncmp("WE", id, 3) == 0)
	{
		if (data->checklist.we == 1)
			exit_with_error("Dup Id in map", data);
		data->checklist.we = 1;
		data->asset_data.west_tex_path = ft_strdup(path);
	}
	else if (ft_strncmp("EA", id, 3) == 0)
	{
		if (data->checklist.ea == 1)
			exit_with_error("Dup Id in map", data);
		data->checklist.ea = 1;
		data->asset_data.east_tex_path = ft_strdup(path);
	}
	else
		assign_texture_north_south(data, id, path);
}

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
	close(fd);
	assign_texture_path(data, id, path);
}

void	validate_all_identifiers_found(t_game *data)
{
	if (!data->checklist.c || !data->checklist.f
		|| !data->checklist.we || !data->checklist.ea
		|| !data->checklist.no || !data->checklist.so
	)
		exit_with_error("the Identifier are not competed check them", data);
}
