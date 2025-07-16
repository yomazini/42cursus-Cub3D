/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:54:24 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/15 17:03:21 by ymazini          ###   ########.fr       */
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr;
	const unsigned char	*s;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	ptr = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	return (dst);
}
