#  Cub3D Project Plan: Youssef & Mehdi

This plan outlines a 4-week schedule to complete the mandatory part of 
Cub3D. It is inspired by a clean, modular code structure (codebase2.0) and leverages 
existing logic from Youssef's so_long for only parsing project to accelerate development.

---

##  The Blueprint: File & Data Structure

This is the most critical first step. You and Mehdi must agree on this 
shared structure before writing any code. This is your contract for 
working together seamlessly.

### 1. Project Directory Structure

cub3D/
├── includes/
│   └── cub3D.h
├── sources/
│   ├── parsing/
│   │   ├── 01_read_file.c
│   │   ├── 02_validate_identifiers.c
│   │   └── 03_validate_map.c
│   ├── rendering/
│   │   ├── 01_init_game.c
│   │   ├── 02_raycasting.c
│   │   ├── 03_drawing.c
│   │   └── event_hooks.c
│   ├── utils/
│   │   └── memory_management.c
│   └── main.c
├── libft/
├── minilibx-linux/
├── assets/
│   ├── maps/
│   │   └── map.cub
│   └── textures/
└── Makefile

### 2. The Core Data Structures (includes/cub3D.h)

This is your project's "brain." A pointer
 to t_cub_data will be passed to nearly every function.
  This avoids global variables and keeps the code clean. 
  The names have been paraphrased to be unique to your project.

`c
// In includes/cub3D.h

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>  // For open
# include <unistd.h> // For read, close
# include <stdio.h>  // For perror
# include <stdlib.h> // For malloc, free, exit
# include <math.h>

// Holds RGB color values (0-255)
typedef struct s_rgb
{
 int red;
 int green;
 int blue;
 int is_set; // Use as a flag to check if color was parsed
} t_rgb;

// Holds all texture and color assets
typedef struct s_assets
{
 char *north_tex_path;
 char *south_tex_path;
 char *west_tex_path;
 char *east_tex_path;
 t_rgb floor_rgb;
 t_rgb ceiling_rgb;
    int     identifier_flags; // Bitmask or counter to check all 6 are found
 void *wall_textures[4]; // N, S, E, W for the renderer
} t_assets;

// Holds all information about the map layout
typedef struct s_scene
{
 char **layout;
 int  height; // Number of rows in the map
 int  width;  // Max width of the map
 double spawn_x;
 double spawn_y;
 char spawn_orientation;
} t_scene;

// The master struct that holds everything
typedef struct s_cub_data
{
 void  *mlx_instance;
 void  *mlx_window;
 t_scene  scene_data;
 t_assets asset_data;
 // t_player player; // Mehdi will add this for player state
} t_cub_data;

/* --- FUNCTION PROTOTYPES --- */

// Reusable from so_long (Youssef)
void free_grid(char **grid);
int  exit_game(t_cub_data *data);

// New cub3D functions
void init_data_structs(t_cub_data *data);
void parse_scene_file(char *filename, t_cub_data *data);
void launch_game(t_cub_data *data);
void exit_with_error(char *message, t_cub_data *data);

#endif