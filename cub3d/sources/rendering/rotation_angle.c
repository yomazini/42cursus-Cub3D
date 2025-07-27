/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_angle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 08:55:21 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/27 09:20:13 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

float	rotation_angle(t_game *game)
{
	if (game->map.spawn_side_face == 'E')
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
