/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:27:12 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/18 17:27:34 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static char	*append_token(char *result, char *token)
{
	char	*temp;

	temp = ft_strjoin(result, token);
	free(result);
	return (temp);
}

static char	*join_all_tokens(char **tokens, int token_count, char *result)
{
	int	i;

	i = 0;
	while (++i < token_count)
	{
		if (i > 1)
		{
			result = append_token(result, " ");
			if (!result)
				return (NULL);
		}
		result = append_token(result, tokens[i]);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*reconstruct_color_string(char **tokens, int token_count)
{
	char	*result;
	int		i;
	int		total_len;

	total_len = 0;
	i = 0;
	while (++i < token_count)
		total_len += ft_strlen(tokens[i]) + 1;
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	return (join_all_tokens(tokens, token_count, result));
}
