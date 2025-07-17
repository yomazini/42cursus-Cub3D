/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_identifiers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:24:06 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/17 18:06:59 by ymazini          ###   ########.fr       */
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
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parse_identifiers(t_list *id_lines, t_game *data)
{
	t_list	*current;
	char	**tokens;
	int i = 0;

	current = id_lines;
	while (current)
	{
		tokens = ft_split((char *)current->content ,' ');
		if (!tokens)
			exit_with_error("malloc failed here", data);
		if (count_tokens(tokens) != 2)
			return ;
//			exit(1);
//			exit_with_error("error in the number of tokens ", data);
		if (!ft_strncmp(tokens[0], "NO", 3) || !ft_strncmp(tokens[0], "SO", 3)
			|| !ft_strncmp(tokens[0], "EA", 3) || !ft_strncmp(tokens[0], "WE", 3))
			parse_texture(tokens, data);
		else if (!ft_strncmp(tokens[0], "F", 2) || !ft_strncmp(tokens[0], "C", 2))
			 parse_color(tokens, data);
			//printf("\n\n\n\n\n\n\nenter the parse color fun\n");
		else
			exit_with_error("Unkown identifire in the file",data);		
		free_grid(tokens);
		current = current->next;
	}
	validate_all_identifiers_found(data);
}

void	parse_texture(char **tokens, t_game *data)
{
	char	*id;
	char	*path;
	int		fd;

	id = tokens[0];
	path = tokens[1];
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_with_error("fd prln", data);
	// printf("%s\n%i\n\n\n\n",path,fd);

		// TODO: Exit WITH ERROR
	close(fd);
	if (ft_strncmp("NO", id, 3) == 0)
	{
		if (data->checklist.no == 1)
			exit_with_error("duplication of Identifier in map ",data);
		data->checklist.no = 1;
		data->asset_data.north_tex_path = ft_strdup(path);
		// if (!data->asset_data.north_tex_path)
			// here free the prev and then call exit_with_error and return && return (NULL);
	}
	if (ft_strncmp("SO", id, 3) == 0)
	{
		if (data->checklist.so == 1)
			exit_with_error("duplication of Identifier in map ", data);
		data->checklist.so = 1;
		data->asset_data.south_tex_path = ft_strdup(path);
		// TODO: PROTET the dup if faild malloc			
	}
	if (ft_strncmp("WE", id, 3) == 0)
	{
		if (data->checklist.we == 1)
			exit_with_error("duplication of Identifier in map", data);
		data->checklist.we = 1;
		data->asset_data.west_tex_path = ft_strdup(path);
		// TODO: protect her 
	}
	if (ft_strncmp("EA", id, 3) == 0)
	{
		if (data->checklist.ea == 1)
			exit_with_error("duplication of Identifier in map ", data);
		data->checklist.ea = 1;
		data->asset_data.east_tex_path = ft_strdup(path);
		// TODO: protect her 
	}
}


void	validate_all_identifiers_found(t_game *data)
{
	if (!data->checklist.c || !data->checklist.f 
		|| !data->checklist.we || !data->checklist.ea
		|| !data->checklist.no || !data->checklist.so
	)
		exit_with_error("the Identifier are not competed check them", data);	
}