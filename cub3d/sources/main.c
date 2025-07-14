/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:23:58 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/14 11:22:56 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void    separate_file_content(t_list *all_lines, t_list **id_lines, t_list **map_lines);
 void	parse_texture(char **tokens, t_game *data);
 void	parse_color(char **tokens, t_game *data);
 void	validate_all_identifiers_found(t_game *data);
 int	count_tokens(char **tokens);
void exit_with_error(char *message, t_game *game);

void parse_identifiers(t_list *id_lines, t_game *data);

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

 int	count_tokens(char **tokens)
{
	int i = 0;
	if (!tokens)
		return 0;
	while (tokens[i])
		i++;
	return i ;
}

void parse_identifiers(t_list *id_lines, t_game *data)
{
	t_list *current;
	char **tokens;

	current = id_lines;
	while(current)
	{
		tokens = ft_split((char *)current->content,' ');
		if (!tokens)
			exit_with_error("malloc failed here",data);
		if (count_tokens(tokens) != 2)
			exit_with_error("error in the number of tokens ",data);
		if ( ft_strncmp(tokens[0],"NO",3) == 0  || ft_strncmp(tokens[0],"SO",3) == 0
				|| ft_strncmp(tokens[0],"SO",3) == 0 || ft_strncmp(tokens[0],"WE",3) == 0)
			parse_texture(tokens,data);
		else if (ft_strncmp(tokens[0],"F",2) == 0 || ft_strncmp(tokens[0],"C",2) == 0 )
			parse_color(tokens,data);
		else 
			exit_with_error("Unkown identifire in the file",data);
		
		free_grid(tokens);
		current = current->next;
	}
	validate_all_identifiers_found(data);

}

 void	parse_color(char **tokens, t_game *data)
 {
	char **rgb_values;
	t_rgb *color_strcut;
	int r;
	int g;
	int b;
	
	rgb_values = ft_split(tokens[1], ',');
	if (!rgb_values || count_tokens(rgb_values) != 3)
		exit_with_error("problem in RGB file",data);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_with_error("RGB color value out of range 0 - 255",data);
	if (ft_strncmp("F",tokens[0],2) == 0)
	{
		if (data->checklist.f == 1)
			exit_with_error("Duplication in the identifiesrs F C ",data);
		data->checklist.f = 1;
		data->asset_data.floor_rgb.red = r;
		data->asset_data.floor_rgb.blue = b;
		data->asset_data.floor_rgb.green = g;
		data->asset_data.floor_rgb.is_set = 1;
	}
	if (ft_strncmp("C",tokens[0],2) == 0)
	{
		if (data->checklist.c == 1)		
			exit_with_error("Duplication in the identifiesrs F C ",data);
		data->checklist.c = 1;
		data->asset_data.ceilllig_rgb.red = r;
		data->asset_data.ceilllig_rgb.blue = b;
		data->asset_data.ceilllig_rgb.green = g;
		data->asset_data.ceilllig_rgb.is_set = 1;
	}
	free_grid(rgb_values);
}


void	validate_all_identifiers_found(t_game *data)
{
	if (!data->checklist.c || !data->checklist.f 
		|| !data->checklist.we || !data->checklist.ea
		|| !data->checklist.no || !data->checklist.so
	)
		exit_with_error("the Identifier are not competed check them",data);	
}


 void	parse_texture(char **tokens, t_game *data)
{
	char *id;
	char *path;
	int fd;

	id = tokens[0];
	path = tokens[1];

	fd = open(path,O_RDONLY);
	if (fd < 0)
		// TODO: Exit WITH ERROR
	close(fd);
		
	// NO SO WE EA
	if (ft_strncmp("NO",id,3) == 0)
	{
		if (data->checklist.no == 1)
			exit_with_error("duplication of Identifier in map ",data);
	
		data->checklist.no = 1;
		data->asset_data.north_tex_path = ft_strdup(path);
		// if (!data->asset_data.north_tex_path)
			// here free the prev and then call exit_with_error and return && return (NULL);
	
	}
	if (ft_strncmp("SO",id,3) == 0)
	{
		if (data->checklist.so == 1)
			exit_with_error("duplication of Identifier in map ",data);
		data->checklist.so = 1;
		data->asset_data.north_tex_path = ft_strdup(path);
		// TODO: PROTET the dup if faild malloc			
		
	}
	if (ft_strncmp("WE",id,3) == 0)
	{
		if (data->checklist.we == 1)
			exit_with_error("duplication of Identifier in map ",data);
		
		data->checklist.we = 1;
		data->asset_data.west_tex_path = ft_strdup(path);
		// TODO: protect her 
	}
	
	if (ft_strncmp("EA",id,3) == 0)
	{
		if (data->checklist.ea == 1)
			exit_with_error("duplication of Identifier in map ",data);
		
		data->checklist.ea = 1;
		data->asset_data.east_tex_path = ft_strdup(path);
		// TODO: protect her 
	}
	

}

int main(int ac, char **av)
{
	t_game game;
	
	game.checklist.so = 0;
	game.checklist.no = 0;
	game.checklist.we = 0;
	game.checklist.ea = 0;
	game.asset_data.ceilllig_rgb.is_set = 0;
	game.asset_data.floor_rgb.is_set = 0;
	
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
	separate_file_content(head_in_main, &id_lines,&map_lines);

	// printf("\n\n\n----this is the first one------\n\n\n");
	
	// while (head_in_main)
	// {
	// 	printf("%s\n",(char *)head_in_main->content);
    // 	head_in_main = head_in_main->next; // Move to the next node
	// }
	// printf("\n\n\n-----this is the 6 componenmts-----\n\n\n");
	// while (id_lines)
	// {
	// 		printf("%s\n",(char *)id_lines->content);
	// 		id_lines = id_lines->next;			
	// }
	
		
	// printf("\n\n\n-----this si the map-----\n\n\n");
	// 	while (map_lines)
	// {
	// 		printf("%s\n",(char *)map_lines->content);
	// 		map_lines = map_lines->next;
			
	// }	

	// printf("\n\n\n----------\n\n\n");
	
	ft_lstclear(&to_freee,free);
	
	ft_prt_tool();

	//* mehdi Part______________________
	
	char map[11][15] = {
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','1','0','1'},
    {'1','0','0','1','0','1','0','0','0','0','0','0','1','0','1'},
    {'1','0','1','1','1','0','0','0','0','0','1','0','1','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','1','0','1','0','1'},
    {'1','0','0','0','0','0','0','0','1','1','1','1','1','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','1','1','1','1','0','0','0','1','1','1','1','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
	};

	int i = 0, j = 0;

	game.map.height = 11;
	game.map.width = 16;

	game.player.x = 1.5 * TILE_SIZE; 
	game.player.y = 1.5 * TILE_SIZE;

	game.map.grid = malloc(sizeof(char *) * game.map.height);
    if (!game.map.grid)
		return (EXIT_FAILURE);
    for (int i = 0; i < game.map.height; i++) 
	{
        game.map.grid[i] = malloc(sizeof(char) * game.map.width);
        if (!game.map.grid[i])
			return (EXIT_FAILURE);
        for (int j = 0; j < game.map.width - 1; j++){
             game.map.grid[i][j] = map[i][j];
        }
         game.map.grid[i][game.map.width - 1] = '\0'; 
    }
	
	intialize_mlx(&game);
}
