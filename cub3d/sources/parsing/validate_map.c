/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:24:09 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/16 13:39:18 by ymazini          ###   ########.fr       */
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
			parse_texture(tokens,data);
		else if (!ft_strncmp(tokens[0], "F", 2) || !ft_strncmp(tokens[0], "C", 2))
			 parse_color(tokens,data);
			//printf("\n\n\n\n\n\n\nenter the parse color fun\n");
		else
			exit_with_error("Unkown identifire in the file",data);		
		free_grid(tokens);
		current = current->next;
	}
	validate_all_identifiers_found(data);
}

void	validate_all_identifiers_found(t_game *data)
{
	if (!data->checklist.c || !data->checklist.f 
		|| !data->checklist.we || !data->checklist.ea
		|| !data->checklist.no || !data->checklist.so
	)
		exit_with_error("the Identifier are not competed check them", data);	
}
