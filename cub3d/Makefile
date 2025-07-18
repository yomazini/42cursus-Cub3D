
NAME		=	cub3D
CC			=	cc
CFLAGS		=	-fsanitize=address -g3 #-Wall -Wextra -Werror -fsanitize=address -g3
RM			=	rm -rf
SRC_DIR		=	sources
OBJ_DIR		=	obj
INC_DIR		=	includes
MLX_DIR		=	minilibx_opengl

SRCS		=	main.c \
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
				rendering/draw_3D.c \
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
				tools/tools1.c \

SRCS_FULL	=	$(addprefix $(SRC_DIR)/, $(SRCS))
OBJS		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_FULL))

HEADERS		=	$(INC_DIR)/cub3D.h

MLX_LIB		=	$(MLX_DIR)/libmlx.a

INCFLAGS	=	-I$(INC_DIR) -I$(MLX_DIR)

# for lunix
# LDFLAGS		=	-L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# for macos
LDFLAGS		=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "✅ $(NAME) is ready!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

mlx:
	@echo "Building MiniLibX..."
	@$(MAKE) -sC $(MLX_DIR)

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJ_DIR)
	@echo "✅ Objects cleaned."

fclean: clean
	@echo "Cleaning executable..."
	@$(RM) $(NAME)
	@echo "✅ Full clean complete."

re: fclean all

bonus:
	@echo "tanchofo mn ba3d hhhh"