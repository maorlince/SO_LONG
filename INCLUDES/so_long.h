/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:58:29 by manon             #+#    #+#             */
/*   Updated: 2025/04/24 21:15:52 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <unistd.h>
#include <stdlib.h>

#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include "../get_next_line/get_next_line.h"
#include "../minilibx-linux/mlx.h"

#define IMG_SIZE 128

// note
// mlxlib makefile path: -L flag
// mlx_init
// mlx_new_window =manage window
// mlx_pixel_put =draw inside window
// mlx_new_image =manipulates image
// mlx_loop =handle keyboard
// makefile -lmx -IXext -IX11

// BAD AND GOOD END
// musique ?
//  ANIMATION? bonus oblige
//  "À chaque mouvement, le compte total de mouvement doit être affiché dans le shell." OBLIGATOIRE
//  BONUS OBLIGE le compte de mouvement est sur la fenetre directementpas sur le shell

// KEYBOARD_MOVES
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

// MAP_INDEX
#define WATER '0'
#define WALL '1'
#define FISH 'C'
#define EXIT 'E'
#define PLAYER 'P'
#define SUMO 'S'

// image format xpm
#define IMG_FISHERMAN "TEXTURES/fisherman.xpm"
#define IMG_FISH "TEXTURES/fish.xpm"
#define IMG_SUMO "TEXTURES/sumo.xpm"
#define IMG_BRIDGE "TEXTURES/bridge.xpm"
#define IMG_CORAL "TEXTURES/coral.xpm"
#define IMG_SAND "TEXTURES/sand.xpm"
#define IMG_EDGE "TEXTURES/edge.xpm"
#define IMG_EDGE_CORNER "TEXTURES/edge_corner.xpm"
#define IMG_WATER "TEXTURES/water.xpm"

// struc flood_fill
typedef struct s_point
{
    int x;
    int y;
} t_point;

// struc map
typedef struct s_map
{
    char **data;
    int width;
    int height;
    int count_fish;
    int count_exit;
    int count_fisherman;
    int count_sumo;
    t_point fisherman_pos;
} t_map;

//struct img
typedef struct s_img
{
    int height;
    int width;
    void *ptr;
} t_img;

// struc game
typedef struct s_game
{
    t_map *map;
    void *mlx_ptr;
    void *win_ptr;    
    t_img edge;
    t_img edge_corner;
    t_img coral;
    t_img water;
    t_img fish;
    t_img bridge;
    t_img fisherman;
    t_img sumo;
    int moves;
} t_game;

// init.c
t_map *init_map(void);
void free_map(t_map *map);
int init_images(t_game *game);
// static void		*load_image(void *mlx, char *path);

// map_loader.c
void count(t_map *map);
char **get_map(char *argv, t_map *map);

// map_checker.c
int check_shape(t_map *map);
int check_wall(t_map *map);
int check_other(t_map *map);

// flood_fill.c
int validate_path(t_map *map);
// static char		**copy_map(char **data, int height);
// static void	fill(char **map, t_point size, t_point cur);

// render.c
void draw_walls(t_game *game, int x, int y);
void draw_others(t_game *game, int x, int y);
void render_map(t_game *game);

// input.c
int key_hook(int keycode, t_game *game);

// move.c
void print_moves(int moves);
int check_moves(t_game *game, t_point new_pos);

// utils.c
void free_copy(char **copy);
int	close_window(t_game *game);

#endif