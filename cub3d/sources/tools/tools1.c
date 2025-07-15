/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:42:44 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/15 14:40:08 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_prt_tool()
{
		// printf("-----------\n\n\n\n\ntooooooooools \n\n");
}
// to free up all 

void free_grid(char **grid)
{
	int i;

	i = 0;
	if (!grid)
		return; 
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	exit_with_error(char *message, t_game *data)
{
	ft_putstr_fd("Error:",2);	
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n',2);
	
	
	if (data)
	{
		if (data->asset_data.north_tex_path)
			free(data->asset_data.north_tex_path);
		if (data->asset_data.south_tex_path)
			free(data->asset_data.south_tex_path);
		if (data->asset_data.east_tex_path)
			free(data->asset_data.east_tex_path);
		if (data->asset_data.west_tex_path)
			free(data->asset_data.east_tex_path);
		if (data->map.grid)
			free_grid(data->map.grid);
		exit(1);

	}
}

 int	count_tokens(char **tokens)
{
	int i = 0;
	if (!tokens)
		return 0;
	while (tokens[i])
		i++;
	return i ;
}
