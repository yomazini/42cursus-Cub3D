/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:23:10 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/09 23:06:46 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h> 
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>

//# include "../MLX/minilibx.h" // TODO: later or not because will switch to mac
# include "../minilibx-linux/mlx.h"


#define NAME "cub3D"
#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 5
#define WALL '1'
#define FLOOR '0'


# define S_KEY	1
# define A_KEY	0
# define W_KEY	13
# define D_KEY	2
# define ESC_KEY	53

# define DOWN_KEY	125
# define UP_KEY		126
# define RIGHT_KEY	124
# define KEY_LEFT	123


//------------------//





// this will hold RGB in the map sep by comma
typedef struct s_rgb
{
	int red;
	int green;
	int blue;
	int is_set; //  check if the F or C been found the susccessfully parsed 
} t_rgb;

// thie hils textures and color assets

typedef struct s_assets
{
	char *north_tex_path;
	char *east_tex_path;
	char *south_tex_path;
	char *west_tex_path;
	t_rgb floor_rgb;
	t_rgb ceilllig_rgb;
	void *wall_textures[4];  // this will hold actual texture images once they are loaded by the MiniLibX library
    //when finds the line NO ./textures/wall.xpm and stores the path in north_tex_path.
	//  Later, Mehdi's call mlx_xpm_file_to_image() using that path, and store the resulting image pointer in data.
	// It centralizes all loaded texture data. (e.g., index 0 for North, 1 for South, etc.) without needing to know the file paths.


	int checker_flag; // track if all identifreir found better
	// i will be set it as 1 and always multiply * 2 {(1*2) 6 times} ==> {(2 - 4 - 8 - 16 - 32 - 64 )} 
	// NO_FLAG = 1, SO_FLAG = 2, WE_FLAG = 4, EA_FLAG = 8, F_FLAG = 16, C_FLAG = 32 and at the end check if equal 64 or otherswise get another structts and each one set as TRUE
	
}t_assets;

typedef struct  s_map
{
	char **grid; // this i will be transfering into int each one atoi '1' ==> 1 {later} 
	int height; // nmr of rows in the map 
	int width; // max width in the map to allocate based on it + 1 of null ; others with "\0" 
	double map_player_x;
	double map_player_y;
	char spawn_side_face; //{N S W E}
	
}	t_map;


typedef struct s_game
{
	void *mlx;
	void *win;
	t_map map;
	int	screen_width; // will be macro later
	int	screen_height; // same
	t_assets asset_data;
//	t_player player;
//	t_img	img;
//	t_ray 	ray;
	//t_player player; // TODO: for mehdi to add this one; 

}t_game;

//-------- Helpers Func ----------//

//void free_grid(char **grid);
//int  exit_game(t_cub_data *data);

//LIB

// Memory and Character Functions
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
void ft_putstr(char *str);
// String Manipulation Functions
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

// File Descriptor Functions
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

// Linked List Struct and Functions
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));


// GNL 
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);



//-------- Parsing Func ----------//




//void free_grid(char **grid);
//int  exit_game(t_game *game);


//-------- Rendring Func ----------//



//-------- testing makefile relink and functionality ----------//
	void ft_prt_pars();
	void ft_prt_rend();
	void ft_prt_tool();

	
#endif
