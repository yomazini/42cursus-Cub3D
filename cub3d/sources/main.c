/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:23:58 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/08 22:41:26 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//int main()
//{
//	ft_prt_pars();
//	ft_prt_rend();
//	ft_prt_tool();
//
//}

int  validate_filename(char *filename)
{
	int str_len = ft_strlen(filename);
	char *extention = ".cub";
	if (str_len < 4)
		return (0);
	return(ft_strncmp(filename + str_len - 4,extention, 4) == 0);
	
}


int main(int ac, char **av)
{
	t_game game;
	(void)game;
	(void)av;
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
	
	ft_prt_tool();

}
