/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:24:09 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/17 21:27:03 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	count_char_in_string(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}


static int	is_string_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if ( str[i] != ' ' && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
//----------
// Working EDITED VERSION; 1.0

// void	parse_color(char **tokens, t_game *data)
// {
// 	char	**rgb_values;
// 	int		r;
// 	int		g;
// 	int		b;

// 	if (count_char_in_string(tokens[1], ',') != 2)
// 		exit_with_error("Invalid RGB format: must have exactly two commas.", data);

// 	rgb_values = ft_split(tokens[1], ',');
// 	if (!rgb_values || count_tokens(rgb_values) != 3)
// 	{
// 		free_grid(rgb_values);
// 		exit_with_error("Invalid RGB format: must have three color values.", data);
// 	}
	
// 	if (!is_string_numeric(rgb_values[0]) || \
// 		!is_string_numeric(rgb_values[1]) || \
// 		!is_string_numeric(rgb_values[2]))
// 	{
// 		free_grid(rgb_values);
// 		exit_with_error("RGB values must be numeric.", data);
// 	}
// 	r = ft_atoi(rgb_values[0]);
// 	g = ft_atoi(rgb_values[1]);
// 	b = ft_atoi(rgb_values[2]);
// 	free_grid(rgb_values);
// 	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
// 		exit_with_error("RGB color value out of range (0-255).", data);
// 	if (ft_strncmp("F", tokens[0], 2) == 0)
// 	{
// 		if (data->checklist.f == 1)
// 			exit_with_error("Duplicate F identifier found.", data);
// 		data->checklist.f = 1;
// 		data->asset_data.floor_rgb.red = r;
// 		data->asset_data.floor_rgb.green = g;
// 		data->asset_data.floor_rgb.blue = b;
// 		data->asset_data.floor_rgb.is_set = TRUE;
// 	}
// 	else if (ft_strncmp("C", tokens[0], 2) == 0)
// 	{
// 		if (data->checklist.c == 1)
// 			exit_with_error("Duplicate C identifier found.", data);
// 		data->checklist.c = 1;
// 		data->asset_data.ceilllig_rgb.red = r;
// 		data->asset_data.ceilllig_rgb.green = g;
// 		data->asset_data.ceilllig_rgb.blue = b;
// 		data->asset_data.ceilllig_rgb.is_set = TRUE;	
// 	}
// }

    // void    parse_color(char **tokens, t_game *data)
    // {
    //     char    **rgb_untrimmed;
    //     char    *trimmed_val;
    //     int     rgb[3];
    //     int     i;

    //     // 1. Validate the raw string: must contain exactly two commas.
    //     if (count_char_in_string(tokens[1], ',') != 2)
    //         exit_with_error("Invalid RGB format: must have exactly two commas.", data);

    //     // 2. Split by comma.
    //     rgb_untrimmed = ft_split(tokens[1], ',');
    //     if (!rgb_untrimmed || count_tokens(rgb_untrimmed) != 3)
    //         exit_with_error("Invalid RGB format: must have three values.", data);
            
    //     i = 0;
    //     while (i < 3)
    //     {
    //         // 3. Trim each part to handle spaces/tabs.
    //         trimmed_val = ft_strtrim(rgb_untrimmed[i], " "); 
    //         if (!is_string_numeric(trimmed_val))
    //             exit_with_error("RGB values must be numeric.", data);
            
    //         // 4. Convert and validate the range.
    //         rgb[i] = ft_atoi(trimmed_val);
    //         if (rgb[i] < 0 || rgb[i] > 255)
    //             exit_with_error("RGB color value out of range (0-255).", data);
    //         free(trimmed_val);
    //         i++;
    //     }
    //     free_grid(rgb_untrimmed);

    //     // 5. Assign the validated colors.
    //     if (ft_strncmp("F", tokens[0], 2) == 0)
    //     {
    //         if (data->checklist.f == 1) exit_with_error("Duplicate F identifier.", data);
    //         data->checklist.f = 1;
    //         data->asset_data.floor_rgb = (t_rgb){rgb[0], rgb[1], rgb[2], 1};
    //     }
    //     else if (ft_strncmp("C", tokens[0], 2) == 0)
    //     {
    //         if (data->checklist.c == 1) exit_with_error("Duplicate C identifier.", data);
    //         data->checklist.c = 1;
    //         data->asset_data.ceilllig_rgb = (t_rgb){rgb[0], rgb[1], rgb[2], 1};
    //     }
    // }
// Helper function: Check if string contains only digits (no spaces allowed)
// static int is_string_purely_numeric(const char *str)
// {
//     int i;

//     i = 0;
//     if (!str || str[0] == '\0')
//         return (0);
//     while (str[i])
//     {
//         if (!ft_isdigit(str[i]))
//             return (0);
//         i++;
//     }
//     return (1);
// }
	
// 	void parse_color(char **tokens, t_game *data)
// {
//     char    **rgb_untrimmed;
//     char    *trimmed_val;
//     int     rgb[3];
//     int     i;

//     // 1. Validate the raw string: must contain exactly two commas.
//     if (count_char_in_string(tokens[1], ',') != 2)
//         exit_with_error("Invalid RGB format: must have exactly two commas.", data);

//     // 2. Split by comma.
//     rgb_untrimmed = ft_split(tokens[1], ',');
//     if (!rgb_untrimmed || count_tokens(rgb_untrimmed) != 3)
//     {
//         free_grid(rgb_untrimmed);
//         exit_with_error("Invalid RGB format: must have three values.", data);
//     }
        
//     i = 0;
//     while (i < 3)
//     {
//         // 3. Trim each part to handle spaces/tabs.
//         trimmed_val = ft_strtrim(rgb_untrimmed[i], " \t");
//         if (!trimmed_val)
//         {
//             free_grid(rgb_untrimmed);
//             exit_with_error("Memory allocation failed.", data);
//         }
        
//         // 4. Check if the trimmed value is purely numeric (no spaces allowed)
//         if (!is_string_purely_numeric(trimmed_val))
//         {
//             free(trimmed_val);
//             free_grid(rgb_untrimmed);
//             exit_with_error("RGB values must be numeric.", data);
//         }
        
//         // 5. Convert and validate the range.
//         rgb[i] = ft_atoi(trimmed_val);
//         if (rgb[i] < 0 || rgb[i] > 255)
//         {
//             free(trimmed_val);
//             free_grid(rgb_untrimmed);
//             exit_with_error("RGB color value out of range (0-255).", data);
//         }
        
//         free(trimmed_val);
//         i++;
//     }
//     free_grid(rgb_untrimmed);

//     // 6. Assign the validated colors.
//     if (ft_strncmp("F", tokens[0], 2) == 0)
//     {
//         if (data->checklist.f == 1) 
//             exit_with_error("Duplicate F identifier.", data);
//         data->checklist.f = 1;
//         data->asset_data.floor_rgb = (t_rgb){rgb[0], rgb[1], rgb[2], 1};
//     }
//     else if (ft_strncmp("C", tokens[0], 2) == 0)
//     {
//         if (data->checklist.c == 1) 
//             exit_with_error("Duplicate C identifier.", data);
//         data->checklist.c = 1;
//         data->asset_data.ceilllig_rgb = (t_rgb){rgb[0], rgb[1], rgb[2], 1};
//     }
// }
// Helper function: Check if string contains only digits (no spaces allowed)
static int is_string_purely_numeric(const char *str)
{
    int i;

    i = 0;
    if (!str || str[0] == '\0')
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

// Helper function to reconstruct color string from tokens
char *reconstruct_color_string(char **tokens, int token_count)
{
    char *result;
    char *temp;
    int i;
    int total_len = 0;
    
    // Calculate total length needed
    for (i = 1; i < token_count; i++)
        total_len += ft_strlen(tokens[i]);
    
    result = malloc(total_len + 1);
    if (!result)
        return NULL;
    
    result[0] = '\0';
    for (i = 1; i < token_count; i++)
    {
        temp = ft_strjoin(result, tokens[i]);
        free(result);
        result = temp;
        if (!result)
            return NULL;
    }
    return result;
}

void parse_color(char **tokens, t_game *data)
{
    char    *color_string;
    char    **rgb_untrimmed;
    char    *trimmed_val;
    int     rgb[3];
    int     i;
    int     token_count;

    token_count = count_tokens(tokens);
    
    // Handle case where color values are split across multiple tokens due to spaces
    if (token_count == 2)
        color_string = ft_strdup(tokens[1]);
    else if (token_count > 2)
        color_string = reconstruct_color_string(tokens, token_count);
    else
        exit_with_error("Invalid color format: missing color values.", data);
    
    if (!color_string)
        exit_with_error("Memory allocation failed.", data);

    // 1. Validate the raw string: must contain exactly two commas.
    if (count_char_in_string(color_string, ',') != 2)
    {
        free(color_string);
        exit_with_error("Invalid RGB format: must have exactly two commas.", data);
    }

    // 2. Split by comma.
    rgb_untrimmed = ft_split(color_string, ',');
    free(color_string);
    
    if (!rgb_untrimmed || count_tokens(rgb_untrimmed) != 3)
    {
        free_grid(rgb_untrimmed);
        exit_with_error("Invalid RGB format: must have three values.", data);
    }
        
    i = 0;
    while (i < 3)
    {
        // 3. Trim each part to handle spaces/tabs.
        trimmed_val = ft_strtrim(rgb_untrimmed[i], " \t");
        if (!trimmed_val)
        {
            free_grid(rgb_untrimmed);
            exit_with_error("Memory allocation failed.", data);
        }
        
        // 4. Check if the trimmed value is purely numeric (no spaces allowed)
        if (!is_string_purely_numeric(trimmed_val))
        {
            free(trimmed_val);
            free_grid(rgb_untrimmed);
            exit_with_error("RGB values must be numeric.", data);
        }
        
        // 5. Convert and validate the range.
        rgb[i] = ft_atoi(trimmed_val);
        if (rgb[i] < 0 || rgb[i] > 255)
        {
            free(trimmed_val);
            free_grid(rgb_untrimmed);
            exit_with_error("RGB color value out of range (0-255).", data);
        }
        
        free(trimmed_val);
        i++;
    }
    free_grid(rgb_untrimmed);

    // 6. Assign the validated colors.
    if (ft_strncmp("F", tokens[0], 2) == 0)
    {
        if (data->checklist.f == 1) 
            exit_with_error("Duplicate F identifier.", data);
        data->checklist.f = 1;
        data->asset_data.floor_rgb = (t_rgb){rgb[0], rgb[1], rgb[2], 1};
    }
    else if (ft_strncmp("C", tokens[0], 2) == 0)
    {
        if (data->checklist.c == 1) 
            exit_with_error("Duplicate C identifier.", data);
        data->checklist.c = 1;
        data->asset_data.ceilllig_rgb = (t_rgb){rgb[0], rgb[1], rgb[2], 1};
    }
}





void	flood_fill_rec(t_game *data, char **grid_copy, int y, int x)
{
	if (y < 0 || y >= data->map.height || x < 0 || x >= data->map.width)
	{
		free_grid(grid_copy);
		exit_with_error("Map is not closed at the edges.", data);
	}
    if (grid_copy[y][x] == ' ')
    {
		free_grid(grid_copy);
		exit_with_error("Map has a hole; floor is adjacent to a space.", data);
	}
	if (grid_copy[y][x] == '1' || grid_copy[y][x] == 'F')
		return;
	grid_copy[y][x] = 'F';
	flood_fill_rec(data, grid_copy, y - 1, x);
	flood_fill_rec(data, grid_copy, y + 1, x);
	flood_fill_rec(data, grid_copy, y, x + 1);
	flood_fill_rec(data, grid_copy, y, x - 1);
}

char	**duplicate_grid(char **grid, int height)
{
	char	**new_grid;
	int		y;

	new_grid = malloc(sizeof(char *) * (height + 1));
	if (!new_grid)
		return (NULL);
	y = 0;
	while (y < height)
	{
		new_grid[y] = ft_strdup(grid[y]);
		if (!new_grid[y])
		{
			free_grid(new_grid);
			return (NULL);
		}
		y++;
	}
	new_grid[y] = NULL;
	return (new_grid);
}

void    validate_walls_are_closed(t_game *data)
{
	char	**map_copy;

	if (data->map.height > 200 && data->map.height > 200)
	{
		//TODO: later free_leaks do not forget that;
		exit_with_error("the map too big; will get stackoverflow.com",data);
	}
		// printf("%d\n%d",data->map.height, data->map.width);
	map_copy = duplicate_grid(data->map.grid, data->map.height);
	if (!map_copy)
		exit_with_error("Malloc failed for map copy.", data);
	flood_fill_rec(data, map_copy,
		(int)data->map.map_player_y, (int)data->map.map_player_x);
	free_grid(map_copy);
}

int	get_max_width(char **grid)
{
	int	i;
	int	max_width;

	max_width = 0; 
	i = 0;
	while (grid[i])
	{
		if (ft_strlen(grid[i]) > max_width)
			max_width = ft_strlen(grid[i]);	
		i++;
	}
	return (max_width);
}

void	normalize_map_grid(t_game *data)
{
	char	**new_grid;
	int		y;

	data->map.width = get_max_width(data->map.grid);
	if (data->map.width == 0)
		exit_with_error("Map content is invalid or empty.", data);
	new_grid = malloc(sizeof(char *) * (data->map.height + 1));
	if (!new_grid)
		exit_with_error("Malloc failed for new grid.", data);
	y = 0;
	while (y < data->map.height)
	{
		new_grid[y] = malloc(sizeof(char) * (data->map.width + 1));
		if (!new_grid[y])
			exit_with_error("Malloc failed for new grid row.", data);
		ft_memset(new_grid[y], ' ', data->map.width);
		ft_memcpy(new_grid[y], data->map.grid[y], ft_strlen(data->map.grid[y]));
		new_grid[y][data->map.width] = '\0';
		y++;
	}
	new_grid[y] = NULL;
	free_grid(data->map.grid);
	data->map.grid = new_grid;
}


void	validate_map_content(t_game *data)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	data->map.player_count = 0;
	while (data->map.grid[y])
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			c = data->map.grid[y][x];
			if (!ft_strchr("01NSWE ", c))
				exit_with_error("Invalid character in map.", data);
			if (ft_strchr("NSWE", c))
			{
				data->map.player_count++;
				data->map.map_player_x = (double)x + 0.5;
				data->map.map_player_y = (double)y + 0.5;
				data->map.spawn_side_face = c;
				data->map.grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (data->map.player_count != 1)
		exit_with_error("Map must have exactly one start position.", data);
}



void	create_map_grid(t_list **map_lines_head, t_game *data)
{
	t_list	*current;
	int		i;

	i = 0;
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
