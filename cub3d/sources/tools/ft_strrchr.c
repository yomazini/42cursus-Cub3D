/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:15:53 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/08 21:16:48 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	int		s_lastindex;

	s_lastindex = ft_strlen(s);
	chr = (char)c;
	if (s[s_lastindex] == chr)
		return ((char *)&s[s_lastindex]);
	s_lastindex -= 1;
	while (0 <= s_lastindex)
	{
		if (s[s_lastindex] == chr)
			return ((char *)&s[s_lastindex]);
		s_lastindex--;
	}
	return (NULL);
}
