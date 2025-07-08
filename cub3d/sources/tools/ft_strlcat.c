/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:01:47 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/08 21:16:48 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	if (!dst && !dstsize)
		return (ft_strlen(src));
	dlen = 0;
	if (dst)
		dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dlen >= dstsize)
		return (dstsize + slen);
	i = 0;
	while (src[i] && (dlen + i) < dstsize - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
