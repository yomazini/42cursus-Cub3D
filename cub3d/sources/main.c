/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:23:58 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/15 13:57:11 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
		data->asset_data.south_tex_path = ft_strdup(path);
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

void	create_map_grid(t_list **map_lines_head, t_game *data)
{
	t_list *current; 
	int i = 0;
	
	data->map.height = ft_lstsize(*map_lines_head);
	if (data->map.height == 0)
	{
		exit_with_error("map is empty",data);
	}
	data->map.grid = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.grid)
		exit_with_error("the allocation in create_map_grid failed",data);
	current = *map_lines_head;
	while (current)
	{
		data->map.grid[i] = ft_strdup((char *)current->content);
		if (!data->map.grid[i])
			exit_with_error("grid allocation failed",data);
		current = current->next;
		i++;
	}
	data->map.grid[i] = NULL;
	ft_lstclear(map_lines_head,free);
}



int main(int ac, char **av)
{

 t_game  game;
    t_list  *all_lines;
    t_list  *id_lines;
    t_list  *map_lines;
    
    if (ac != 2)
    {
        ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2);
        return (1);
    }
    // Zero out the entire game struct to initialize all pointers to NULL
    // and all flags/ints to 0. This is the safest way to start.
    ft_memset(&game, 0, sizeof(t_game));
    
    if (validate_filename(av[1]) == 0)
        exit_with_error("Invalid file extension. Must be .cub", &game);

    // 1. Read the entire file into one list.
    all_lines = read_file_to_list(av[1]);
    if (!all_lines)
        exit_with_error("File is empty or could not be read.", &game);

    // 2. Separate the content into two new lists.
    id_lines = NULL;
    map_lines = NULL;
    separate_file_content(all_lines, &id_lines, &map_lines);
    
    // 3. The original list is no longer needed. Free it immediately.
    ft_lstclear(&all_lines, free);

    // 4. Parse the identifier list, then free it.
    parse_identifiers(id_lines, &game);
    ft_lstclear(&id_lines, free);
    
    // 5. Create the map grid from the map list.
    //    (The create_map_grid function will free the map_lines list itself).
    create_map_grid(&map_lines, &game);

    // 6. You can now proceed with map validation...
    printf("---PARSED MAP---\n");
    int i = 0;
    while(game.map.grid[i])
    {
        printf("%s\n", game.map.grid[i]);
        i++;
    }
    
    // Final cleanup at the end (will be part of your exit_game function)
    free_grid(game.map.grid);
    // You would also free your texture paths here.


	//* mehdi Part______________________
	
	// char map[11][15] = {
    // {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
    // {'1','0','0','0','0','0','0','0','0','0','0','0','1','0','1'},
    // {'1','0','0','1','0','1','0','0','0','0','0','0','1','0','1'},
    // {'1','0','1','1','1','0','0','0','0','0','1','0','1','0','1'},
    // {'1','0','0','0','0','0','0','0','0','0','1','0','1','0','1'},
    // {'1','0','0','0','0','0','0','0','1','1','1','1','1','0','1'},
    // {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    // {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    // {'1','1','1','1','1','1','0','0','0','1','1','1','1','0','1'},
    // {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    // {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
	// };

	// int i = 0, j = 0;

	// game.map.height = 11;
	// game.map.width = 16;

	// game.player.x = 1.5 * TILE_SIZE; 
	// game.player.y = 1.5 * TILE_SIZE;

	// game.map.grid = malloc(sizeof(char *) * game.map.height);
    // if (!game.map.grid)
	// 	return (EXIT_FAILURE);
    // for (int i = 0; i < game.map.height; i++) 
	// {
    //     game.map.grid[i] = malloc(sizeof(char) * game.map.width);
    //     if (!game.map.grid[i])
	// 		return (EXIT_FAILURE);
    //     for (int j = 0; j < game.map.width - 1; j++){
    //          game.map.grid[i][j] = map[i][j];
    //     }
    //      game.map.grid[i][game.map.width - 1] = '\0'; 
    // }
	
	// intialize_mlx(&game);

}
