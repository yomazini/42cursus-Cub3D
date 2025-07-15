/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:01:26 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/15 14:39:18 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_prt_pars()
{
	printf("this is parseee\n\n");
}

static char *ft_trim_new_line(char *line)
{
	int len;
		if (!line)
			return NULL;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		return (line);
}

t_list *read_file_to_list(char *filename)
{
	int fd;
	char *line;
	t_list *new_node;
	t_list *head_list;

	head_list = NULL;
	fd =  open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("can not open the file\n",2);
		exit(1);
	}
	while(TRUE)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		new_node = ft_lstnew(ft_trim_new_line(line));
		if (!new_node)
		{
			// must free if something before it;
			free(line);
			ft_lstclear(&head_list,free);
			ft_putstr_fd("malloc failed in file reading",2);
		}
		ft_lstadd_back(&head_list, new_node);
//		free(line);
	}
	close(fd);
	return (head_list);
}

 int  validate_filename(char *filename)
{
	int str_len = ft_strlen(filename);
	char *extention = ".cub";
	if (str_len < 4)
		return (0);
	return(ft_strncmp(filename + str_len - 4,extention, 4) == 0);
}