
NAME		=	cub3D
CC			=	cc
CFLAGS		=	#-Wall -Wextra -Werror -Ofast
DEBUG_FLAGS	=	-g3 -fsanitize=address
RM			=	rm -rf

MAND_DIR	=	Mandatory
BONUS_DIR	=	Bonus
MLX_DIR		=	minilibx_opengl

MAND_SRC_DIR	=	$(MAND_DIR)/sources
MAND_INC_DIR	=	$(MAND_DIR)/includes
MAND_OBJ_DIR	=	$(MAND_DIR)/obj

BONUS_SRC_DIR	=	$(BONUS_DIR)/sources
BONUS_INC_DIR	=	$(BONUS_DIR)/includes
BONUS_OBJ_DIR	=	$(BONUS_DIR)/obj

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
				rendering/my_mlx_pixel_put_minimap.c \
				rendering/fexit.c \
				rendering/mouse_move.c \
				rendering/draw_3D.c \
				rendering/render_minimap.c \
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
				rendering/my_mlx_pixel_put_minimap.c \
				rendering/draw_3D.c \
				rendering/fexit.c \
				rendering/mouse_move.c \
				rendering/render_minimap.c \
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

MAND_SRCS_FULL	=	$(addprefix $(MAND_SRC_DIR)/, $(MAND_SRCS))
MAND_OBJS		=	$(patsubst $(MAND_SRC_DIR)/%.c, $(MAND_OBJ_DIR)/%.o, $(MAND_SRCS_FULL))

BONUS_SRCS_FULL	=	$(addprefix $(BONUS_SRC_DIR)/, $(BONUS_SRCS))
BONUS_OBJS		=	$(patsubst $(BONUS_SRC_DIR)/%.c, $(BONUS_OBJ_DIR)/%.o, $(BONUS_SRCS_FULL))

MAND_HEADERS	=	$(MAND_INC_DIR)/cub3D.h
BONUS_HEADERS	=	$(BONUS_INC_DIR)/cub3D_bonus.h

MLX_LIB		=	$(MLX_DIR)/libmlx.a

MAND_INCFLAGS	=	-I$(MAND_INC_DIR) -I$(MLX_DIR)
BONUS_INCFLAGS	=	-I$(BONUS_INC_DIR) -I$(MLX_DIR)

LDFLAGS		=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lm

RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
MAGENTA		=	\033[0;35m
CYAN		=	\033[0;36m
WHITE		=	\033[0;37m
RESET		=	\033[0m

BONUS_FLAG	=	.bonus

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "$(YELLOW)Building MiniLibX...$(RESET)"
	@$(MAKE) -sC $(MLX_DIR)
	@echo "$(GREEN)✅ MiniLibX built successfully!$(RESET)"

$(NAME): $(MAND_OBJS) $(MLX_LIB)
	@if [ -f $(BONUS_FLAG) ]; then \
		echo "$(YELLOW)Removing bonus objects for mandatory build...$(RESET)"; \
		$(RM) $(BONUS_OBJ_DIR) $(BONUS_FLAG); \
	fi
	@echo "$(YELLOW)Linking $(NAME) (mandatory)...$(RESET)"
	@$(CC) $(CFLAGS) $(MAND_OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) (mandatory) is ready!$(RESET)"

$(MAND_OBJ_DIR)/%.o: $(MAND_SRC_DIR)/%.c $(MAND_HEADERS)
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling mandatory: $<$(RESET)"
	@$(CC) $(CFLAGS) $(MAND_INCFLAGS) -c $< -o $@

bonus: $(MLX_LIB) $(BONUS_OBJS) $(BONUS_FLAG)
	@echo "$(YELLOW)Linking $(NAME) (bonus)...$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) (bonus) is ready!$(RESET)"

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c $(BONUS_HEADERS)
	@mkdir -p $(dir $@)
	@echo "$(MAGENTA)Compiling bonus: $<$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_INCFLAGS) -c $< -o $@

$(BONUS_FLAG): 
	@if [ -f $(NAME) ]; then \
		echo "$(YELLOW)Removing mandatory objects for bonus build...$(RESET)"; \
		$(RM) $(MAND_OBJ_DIR) $(NAME); \
	fi
	@touch $(BONUS_FLAG)

# Clean object files
clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(RM) $(MAND_OBJ_DIR) $(BONUS_OBJ_DIR)
	@$(RM) $(BONUS_FLAG)
	@echo "$(GREEN)✅ Objects cleaned.$(RESET)"

# Full clean
fclean: clean
	@echo "$(YELLOW)Cleaning executable and MiniLibX...$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -sC $(MLX_DIR) clean 2>/dev/null || true
	@echo "$(GREEN)✅ Full clean complete.$(RESET)"

re: fclean all

re_bonus: fclean bonus
