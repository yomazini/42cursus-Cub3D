/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:17:24 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/15 09:24:25 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
		angle = angle + (2 * PI);
	return (angle);
}
