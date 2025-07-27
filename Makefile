NAME		=	cub3D
BONUS		=	cub3D_bonus
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address 
RM			=	rm -rf

MAND_DIR	=	Mandatory
BONUS_DIR	=	Bonus
MLX_DIR		=	minilibx_opengl

MAND_SRCS	=	cub3D.c \
				parsing/parsing.c \
				parsing/read_file.c \
				parsing/parsing_tools.c \
				parsing/map_creation.c \
				parsing/validate_identifiers.c \
				parsing/parsing_colors_helpers.c \
				parsing/validate_map.c \
				parsing/validate_map2.c \
				rendering/ft_render.c \
				rendering/intialize_mlx.c \
				rendering/normalize_angle.c \
				rendering/cast_rays.c \
				rendering/update_player.c \
				rendering/raycastion_tools.c \
				rendering/cast_one_ray.c \
				rendering/my_mlx_pixel_put.c \
				rendering/fexit.c \
				rendering/cleanup_textures.c \
				rendering/draw_3D.c \
				rendering/load_textures.c \
				rendering/render_3d.c \
				rendering/rotation_angle.c \
				tools/ft_atoi.c \
				tools/ft_isalnum.c \
				tools/ft_isalpha.c \
				tools/ft_isdigit.c \
				tools/ft_itoa.c \
				tools/ft_lstadd_back_bonus.c \
				tools/ft_lstadd_front_bonus.c \
				tools/ft_lstclear_bonus.c \
				tools/ft_lstdelone_bonus.c \
				tools/ft_lstlast_bonus.c \
				tools/ft_lstnew_bonus.c \
				tools/ft_lstsize_bonus.c \
				tools/ft_putchar_fd.c \
				tools/ft_putstr_fd.c \
				tools/ft_split.c \
				tools/ft_strchr.c \
				tools/ft_strdup.c \
				tools/ft_strjoin.c \
				tools/ft_strlcat.c \
				tools/ft_strlcpy.c \
				tools/ft_strlen.c \
				tools/ft_strncmp.c \
				tools/ft_strrchr.c \
				tools/ft_strtrim.c \
				tools/ft_substr.c \
				tools/gnl.c \
				tools/tools1.c

BONUS_SRCS	=	cub3D_bonus.c \
				parsing/parsing_bonus.c \
				parsing/read_file_bonus.c \
				parsing/parsing_tools_bonus.c \
				parsing/map_creation_bonus.c \
				parsing/validate_identifiers_bonus.c \
				parsing/parsing_colors_helpers_bonus.c \
				parsing/validate_map_bonus.c \
				parsing/validate_map2_bonus.c \
				rendering/ft_render_bonus.c \
				rendering/intialize_mlx_bonus.c \
				rendering/normalize_angle_bonus.c \
				rendering/cast_rays_bonus.c \
				rendering/update_player_bonus.c \
				rendering/raycastion_tools_bonus.c \
				rendering/cast_one_ray_bonus.c \
				rendering/my_mlx_pixel_put_bonus.c \
				rendering/my_mlx_pixel_put_minimap_bonus.c \
				rendering/fexit_bonus.c \
				rendering/cleanup_texture_bonus.c \
				rendering/mouse_move_bonus.c \
				rendering/draw_3D_bonus.c \
				rendering/render_minimap_bonus.c \
				rendering/load_textures_bonus.c \
				rendering/render_3d_bonus.c \
				rendering/rotation_angle_bonus.c \
				tools/ft_atoi_bonus.c \
				tools/ft_isalnum_bonus.c \
				tools/ft_isalpha_bonus.c \
				tools/ft_isdigit_bonus.c \
				tools/ft_itoa_bonus.c \
				tools/ft_lstadd_back_bonus.c \
				tools/ft_lstadd_front_bonus.c \
				tools/ft_lstclear_bonus.c \
				tools/ft_lstdelone_bonus.c \
				tools/ft_lstlast_bonus.c \
				tools/ft_lstnew_bonus.c \
				tools/ft_lstsize_bonus.c \
				tools/ft_putchar_fd_bonus.c \
				tools/ft_putstr_fd_bonus.c \
				tools/ft_split_bonus.c \
				tools/ft_strchr_bonus.c \
				tools/ft_strdup_bonus.c \
				tools/ft_strjoin_bonus.c \
				tools/ft_strlcat_bonus.c \
				tools/ft_strlcpy_bonus.c \
				tools/ft_strlen_bonus.c \
				tools/ft_strncmp_bonus.c \
				tools/ft_strrchr_bonus.c \
				tools/ft_strtrim_bonus.c \
				tools/ft_substr_bonus.c \
				tools/gnl_bonus.c \
				tools/tools1_bonus.c

OBJS		=	$(SRCS:.c=.o)
OBJB		=	$(SRCB:.c=.o)

SRCS		=	$(addprefix $(MAND_DIR)/sources/, $(MAND_SRCS))
SRCB		=	$(addprefix $(BONUS_DIR)/sources/, $(BONUS_SRCS))

HEADM		=	$(MAND_DIR)/includes/cub3D.h
HEADB		=	$(BONUS_DIR)/includes/cub3D_bonus.h

LDFLAGS		=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -sC $(MLX_DIR) 2>/dev/null || echo "Warning: MiniLibX not found"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJS): %.o:%.c $(HEADM) Makefile
	@$(CC) $(CFLAGS) -I$(MAND_DIR)/includes -I$(MLX_DIR) -c $< -o $@

bonus: $(BONUS)

$(BONUS): $(OBJB)
	@$(MAKE) -sC $(MLX_DIR) 2>/dev/null || echo "Warning: MiniLibX not found"
	@$(CC) $(CFLAGS) $(OBJB) $(LDFLAGS) -o $(BONUS)

$(OBJB): %.o:%.c $(HEADB) Makefile
	@$(CC) $(CFLAGS) -I$(BONUS_DIR)/includes -I$(MLX_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(OBJB) 

fclean: clean
	@$(RM) $(NAME) $(BONUS) $(OBJB)

re: fclean all
