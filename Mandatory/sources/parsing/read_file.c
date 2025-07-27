/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:24:03 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/27 20:41:23 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_line_empty(char *line)
{
	if (line[0] == '\n')
		return (TRUE);
	return (FALSE);
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (ft_strchr("01", line[i]) != NULL);
}

static void	handle_line_split(char *line_content,
		int *map_has_started, t_list **id_lines, t_list **map_lines)
{
	if (*map_has_started == FALSE && is_map_line(line_content))
		*map_has_started = TRUE;
	if (*map_has_started)
	{
		if (line_content[0] == '\n')
			exit_with_error("check the map", NULL);
		ft_lstadd_back(map_lines, ft_lstnew(ft_strdup(line_content)));
	}
	else
		ft_lstadd_back(id_lines, ft_lstnew(ft_strdup(line_content)));
}

void	separate_file_content(t_list *all_lines,
		t_list **id_lines, t_list **map_lines)
{
	t_list	*current_node;
	char	*line_content;
	int		map_has_started;

	map_has_started = FALSE;
	current_node = all_lines;
	while (current_node)
	{
		line_content = (char *)current_node->content;
		if (is_line_empty(line_content))
		{
			if (map_has_started == TRUE)
			{
				ft_putstr_fd("line empty inside the map\n", 2);
				exit(1);
			}
			current_node = current_node->next;
			continue ;
		}
		handle_line_split(line_content, &map_has_started, id_lines, map_lines);
		current_node = current_node->next;
	}
}

t_list	*read_file_to_list(char *filename)
{
	int		fd;
	char	*line;
	t_list	*head_list;
	int		reach_map;

	reach_map = FALSE;
	head_list = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("can not open the file\n", 2);
		exit(1);
	}
	while (TRUE)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		handle_line(line, &reach_map, &head_list);
	}
	close(fd);
	return (head_list);
}
