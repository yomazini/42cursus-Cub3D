/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:01:26 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/26 17:34:08 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static char	*ft_trim_new_line(char *line)
{
	int	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

int	validate_filename(char *filename)
{
	int		str_len;
	char	*extention;

	extention = ".cub";
	str_len = ft_strlen(filename);
	if (str_len < 4)
		return (0);
	return (ft_strncmp(filename + str_len - 4, extention, 4) == 0);
}

static int	check_newline_cases(char *line,
	int *reach_map, char *to_test_map_reach)
{
	if (line[0] == '\n' && *reach_map == FALSE)
	{
		(free(to_test_map_reach), free(line));
		return (0);
	}
	if (line[0] == '\n' && *reach_map == TRUE)
	{
		(free(to_test_map_reach), free(line));
		exit_with_error("Ops Trickkkky NL", NULL);
	}
	return (1);
}

static void	create_and_add_node(char *line, t_list **head_list,
								char *to_test_map_reach)
{
	t_list	*new_node;
	char	*trimmed_line;

	trimmed_line = ft_trim_new_line(line);
	new_node = ft_lstnew(ft_strdup(trimmed_line));
	free(line);
	if (!new_node || !new_node->content)
	{
		free(to_test_map_reach);
		ft_lstclear(head_list, free);
		exit(1);
	}
	ft_lstadd_back(head_list, new_node);
}

int	handle_line(char *line, int *reach_map, t_list **head_list)
{
	char	*to_test_map_reach;

	to_test_map_reach = ft_strtrim(line, " ");
	if (!to_test_map_reach)
	{
		free(line);
		exit_with_error("alloc failed in trim", NULL);
	}
	if (to_test_map_reach[0] == '1')
		*reach_map = TRUE;
	if (!check_newline_cases(line, reach_map, to_test_map_reach))
		return (0);
	create_and_add_node(line, head_list, to_test_map_reach);
	free(to_test_map_reach);
	return (1);
}
