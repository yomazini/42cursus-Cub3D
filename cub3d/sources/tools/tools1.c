/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:42:44 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/09 22:37:51 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_prt_tool()
{
		printf("-----------\n\n\n\n\ntooooooooools \n\n");
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