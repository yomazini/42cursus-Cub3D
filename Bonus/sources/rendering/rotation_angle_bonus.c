/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_angle_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 08:55:21 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/28 11:12:14 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

float	rotation_angle(t_game *game)
{
	if (game->map.side_face == 'E')
		return (0);
	else if (game->map.side_face == 'N')
		return (1.5 * PI);
	else if (game->map.side_face == 'W')
		return (PI);
	else if (game->map.side_face == 'S')
		return (PI / 2);
	else
		return (-1);
}
