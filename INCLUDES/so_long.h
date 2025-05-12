/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:58:29 by manon             #+#    #+#             */
/*   Updated: 2025/05/12 19:25:23 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

//makefile obj?

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../minilibx-linux/mlx.h"

# define IMG_SIZE 32

// KEYBOARD_MOVES
# define KEY_QQ 113
# define KEY_Q 81
# define KEY_YY 121
# define KEY_Y 89
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// MAP_INDEX
# define WATER '0'
# define WALL '1'
# define FISH 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define MAELSTROM 'S'

// image format xpm
# define IMG_FISHERMAN "TEXTURES/fisherman.xpm"
# define IMG_FISH "TEXTURES/fish.xpm"
# define IMG_MAELSTROM "TEXTURES/maelstrom.xpm"
# define IMG_BRIDGE "TEXTURES/bridge.xpm"
# define IMG_CORAL "TEXTURES/coral.xpm"
# define IMG_EDGE1 "TEXTURES/edge1.xpm"
# define IMG_EDGE2 "TEXTURES/edge2.xpm"
# define IMG_EDGE3 "TEXTURES/edge3.xpm"
# define IMG_EDGE4 "TEXTURES/edge4.xpm"
# define IMG_EDGE_CORNER1 "TEXTURES/edge_corner1.xpm"
# define IMG_EDGE_CORNER2 "TEXTURES/edge_corner2.xpm"
# define IMG_EDGE_CORNER3 "TEXTURES/edge_corner3.xpm"
# define IMG_EDGE_CORNER4 "TEXTURES/edge_corner4.xpm"
# define IMG_WATER "TEXTURES/water.xpm"
# define IMG_WAVES "TEXTURES/waves.xpm"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	*stash;
	char	*tmp;
	char	*line;
	char	**data;
	int		width;
	int		height;
	int		count_fish;
	int		count_exit;
	int		count_fisherman;
	int		count_maelstrom;
	t_point	fisherman_pos;
}	t_map;

typedef struct s_img
{
	int		height;
	int		width;
	void	*ptr;
}	t_img;

typedef struct s_game
{
	char			lvl;
	t_point			add_pos[4];
	int				held_key;
	int				water_frame;
	void			*mlx_ptr;
	void			*win_ptr;
	unsigned long	last_update;
	int				moves;
	t_map			*map;
	t_img			edge1;
	t_img			edge2;
	t_img			edge3;
	t_img			edge4;
	t_img			edge_corner1;
	t_img			edge_corner2;
	t_img			edge_corner3;
	t_img			edge_corner4;
	t_img			coral;
	t_img			water;
	t_img			waves;
	t_img			fish;
	t_img			bridge;
	t_img			fisherman;
	t_img			maelstrom;
	t_img			black_tile;
}	t_game;

// init.c
t_map			*init_map(void);
void			free_map(t_map *map);
int				init_images(t_game *game);
//static void		loader(t_game *game);
// static void	*load_image(void *mlx, char *path);

// map_loader.c

//static void	count_utils(t_game *game, char data)
int				count(t_game *game);
char			**get_map(char *argv, t_map *map);

// map_checker.c
int				check_shape(t_map *map);
int				check_wall(t_map *map);
int				check_other(t_map *map);

// flood_fill.c
int				validate_path(t_map *map);
// static char	**copy_map(char **data, int height);
// static void	fill(char **map, t_point size, t_point cur);

//bonus.c
void			init_black_tile(t_game *game);
void			dark_mode(t_game *game);
void			draw_shadow(t_game *game, int x, int y);

// render.c
void			draw_edge_corner(t_game *game, int x, int y);
void			draw_edge(t_game *game, int x, int y);
void			draw_walls(t_game *game, int x, int y);
void			draw_others(t_game *game, int x, int y);
void			render_map(t_game *game);

// input.c
int				key_hook(int keycode, t_game *game);

// utils.c
int				close_window(t_game *game);
void			free_copy(char **copy);
void			supp_edge(t_game *game);
void			quit_game(t_game *game);
void			song(t_game *game);

// move.c
int				check_moves(t_game *game, t_point new_pos);
void			display_moves(t_game *game);

//maelstrom.c
void			search_maelstrom(t_game *game);
void			move_maelstrom(t_game *game, int x, int y);
unsigned long	get_time(void);
int				loop_hook(t_game *game);

#endif