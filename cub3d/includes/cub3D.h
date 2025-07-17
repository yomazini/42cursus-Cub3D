/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:23:10 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/17 11:19:44 by eel-garo         ###   ########.fr       */
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
# include <stdbool.h>
# include "../minilibx_opengl/mlx.h"
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define TILE_SIZE 64
#define MINIMAP_SCALE_FACTOR 0.3

#define PI 3.1415926535
#define FOV (60 * (PI / 180.0))
#define NAME "cub3D"
#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 5
#define WALL '1'
#define FLOOR '0'

# define KEY_W        13
# define KEY_A         0
# define KEY_S         1
# define KEY_D         2
# define KEY_ESC      53

# define KEY_UP      126
# define KEY_LEFT    123
# define KEY_RIGHT   124
# define KEY_DOWN    125


//------------------//

typedef struct s_rgb
{
	int red;
	int green;
	int blue;
	int is_set;
} t_rgb;

typedef struct s_assets
{
	char *north_tex_path;
	char *east_tex_path;
	char *south_tex_path;
	char *west_tex_path;
	t_rgb floor_rgb;
	t_rgb ceilllig_rgb;
	void *wall_textures[4]; 
	int checker_flag; 
	
}t_assets;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
typedef struct  s_map
{
	char **grid;
	int height;
	int width;
	double map_player_x;
	double map_player_y;
	char spawn_side_face;
	int player_count;
}	t_map;

typedef struct  s_id_checker
{
	int no;
	int ea;
	int so;
	int f;
	int we;
	int c;
}t_id_checker;

typedef struct s_imag
{
	void	*img_ptr;
	char	*addr;
	int		bpp; // Bits per pixel x - COL
	int		line_len; // Bytes per line y - ROWS
	int		endian;
}	t_img;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	horzhit_x;
	float	horzhit_y;
	float	verthit_x;
	float	verthit_y;
	float	distance;
	bool	is_ray_facing_up;
	bool	is_ray_facing_down;
	bool	is_ray_facing_left;
	bool	is_ray_facing_right;
	bool	was_hit_vertical;
}	t_ray;

typedef struct s_player
{
	float	x;
	float	y;
	float	rotation_angle;
	int		turn_direction; // -1 for left, +1 for right
	int    strafe_direction;
	int		walk_direction; // -1 for back, +1 for forward 
	float	move_speed;
	float	rotation_speed;
}	t_player;


typedef struct	s_dda
{
	float	y_intercept;
	float	x_intercept;
	float	x_step;
	float	y_step;
	float	next_x;
	float	next_y;
}	t_dda;

typedef struct s_line
{
	float	dx;
	float	dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
}	t_line;

typedef struct s_3d_data
{
	float	dist_to_proj_plane;
	float	projected_wall_height;
	float	corrected_dist;
	int		wall_top_pixel;
	int		wall_bottom_pixel;	
}	t_3d;

typedef struct s_update_player
{
	float	move_step;
	float	move_x;
	float	move_y;
	float	new_x;
	float	new_y;
	float   strafe_angle;
	float   strafe_step;
}	t_p;

typedef struct s_game
{
	void *mlx;
	void *win;
	t_map map;
	int	screen_width;
	int	screen_height;
	t_assets asset_data;
	t_img	img;
	t_ray 	rays[WINDOW_WIDTH];
	t_player player;
	t_id_checker checklist; 
}t_game;

//LIB
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
void ft_putstr(char *str);
void	*ft_memset(void *b, int c, size_t len);
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
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);


//-------- Parsing Func ----------//

void	separate_file_content(t_list *all_lines, t_list **id_lines, t_list **map_lines);
void	create_map_grid(t_list **map_lines_head, t_game *data);
void	parse_texture(char **tokens, t_game *data);
void	parse_color(char **tokens, t_game *data);
void	validate_all_identifiers_found(t_game *data);
int		count_tokens(char **tokens);
void	parse_identifiers(t_list *id_lines, t_game *data);
void	separate_file_content(t_list *all_lines, t_list **id_lines, t_list **map_lines);
t_list	*read_file_to_list(char *filename);
int		validate_filename(char *filename);
void	validate_map_content(t_game *data);
void	validate_walls_are_closed(t_game *data);
void	validate_walls_are_closed(t_game *data);
void	flood_fill_rec(t_game *data, char **grid_copy, int y, int x);
int		get_max_width(char **grid);
void	normalize_map_grid(t_game *data);
void	parse_identifiers(t_list *id_lines, t_game *data);


//-------- Helpers Func ----------//

void	exit_with_error(char *message, t_game *game);
void	free_grid(char **grid);
int 	exit_game(t_game *game);

//-------- Rendring Func ----------//
bool	intialize_mlx(t_game *game);
void	ft_render(t_game *game);
float	normalize_angle(float angle);
void	cast_rays(t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
bool	hit_wall(t_game *game, float x, float y);
void	update_player(t_game *game);
void 	draw_line(t_game *game, float x1, float y1, float x2, float y2);
float 	distance(float x1, float y1, float x2, float y2);
void	draw_line(t_game *game, float x1, float y1, float x2, float y2);
void	initiatize_rayfacing(t_game *game, float ray_angle, int i);
void	cast_one_ray(t_game *game , int i);
void	store_final_hit(t_game *game, float h_dist, float v_dist, int i);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	render_3d_projaction(t_game *game);

#endif
