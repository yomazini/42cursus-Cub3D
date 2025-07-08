/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:54:24 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/08 21:16:48 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*ft_strchr(const char *s, int c)
{
	char	chr;
	int		i;

	chr = (char) c;
	i = -1;
	while (s[++i])
	{
		if (s[i] == chr)
			return ((char *)&s[i]);
	}
	if (s[i] == chr)
		return ((char *)&s[i]);
	return (NULL);
}
