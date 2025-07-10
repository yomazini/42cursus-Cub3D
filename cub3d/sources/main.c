/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:23:58 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/09 23:24:39 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void    separate_file_content(t_list *all_lines, t_list **id_lines, t_list **map_lines);


char *ft_trim_new_line(char *line)
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
	}
	close(fd);
	return (head_list);
}

static int  validate_filename(char *filename)
{
	int str_len = ft_strlen(filename);
	char *extention = ".cub";
	if (str_len < 4)
		return (0);
	return(ft_strncmp(filename + str_len - 4,extention, 4) == 0);
}


static int is_line_empty(char *line)
{
	if (line[0] == '\n')
		return (TRUE);
	return (FALSE);
}

static int is_map_line(char *line)
{
	int i = 0;
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == WALL)
		return (TRUE);
	return (FALSE);
}

void    separate_file_content(t_list *all_lines, t_list **id_lines, t_list **map_lines)
{
	t_list *current_node;
	char *line_content;
	int map_has_started;

	map_has_started = 0;
	current_node = all_lines;
	while (current_node)
	{
		line_content = (char *)current_node->content;
		if (is_line_empty(line_content))
		{
			if (map_has_started == TRUE)
			{
				ft_putstr_fd("line apnlty inside the map\n",2);
				exit (1); //TODO: later will call garbage collector or just return and free on the main
			}
			current_node = current_node->next;
			continue;
		}
		if (map_has_started == FALSE && is_map_line(line_content))
			map_has_started = 1;
		if (map_has_started)
			ft_lstadd_back(map_lines,ft_lstnew(ft_strdup(line_content)));
		else 
			ft_lstadd_back(id_lines, ft_lstnew(ft_strdup(line_content)));
		current_node = current_node->next;
	}
}

int main(int ac, char **av)
{
	t_game game;
	(void)game;
	(void)av;
	t_list *head_in_main;
	t_list *to_freee;

	t_list *id_lines;
	t_list *map_lines;
	
	id_lines = NULL;
	map_lines = NULL;
	
	head_in_main = NULL;
	to_freee = NULL;
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3D <map.cub>\n",2);
		return(1);
	}
	if (validate_filename(av[1]) == 0)
	{
		ft_putstr_fd("map validation Failed\n",2);	
		return (1);
	}
	head_in_main = read_file_to_list(av[1]);
	to_freee = head_in_main;
	separate_file_content(head_in_main, &id_lines,&map_lines );

	printf("\n\n\n----this is the first one------\n\n\n");
	
	while (head_in_main)
	{
		printf("%s\n",(char *)head_in_main->content);
    	head_in_main = head_in_main->next; // Move to the next node
	}
	printf("\n\n\n-----this is the 6 componenmts-----\n\n\n");
	while (id_lines)
	{
			printf("%s\n",(char *)id_lines->content);
			id_lines = id_lines->next;			
	}
	
		
	printf("\n\n\n-----this si the map-----\n\n\n");
		while (map_lines)
	{
			printf("%s\n",(char *)map_lines->content);
			map_lines = map_lines->next;
			
	}	

	printf("\n\n\n----------\n\n\n");
	
	ft_lstclear(&to_freee,free);
	
	ft_prt_tool();

}
