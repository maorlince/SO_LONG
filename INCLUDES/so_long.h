/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:58:29 by manon             #+#    #+#             */
/*   Updated: 2025/05/03 18:58:19 by manon            ###   ########.fr       */
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

// struc flood_fill
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// struc map
typedef struct s_map
{
	char	**data;
	int		width;
	int		height;
	int		count_fish;
	int		count_exit;
	int		count_fisherman;
	int		count_maelstrom;
	t_point	fisherman_pos;
}	t_map;

// struct img
typedef struct s_img
{
	int		height;
	int		width;
	void	*ptr;
}	t_img;

// struc game
typedef struct s_game
{
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
}	t_game;

// init.c
t_map			*init_map(void);
void			free_map(t_map *map);
int				init_images(t_game *game);
// static void	*load_image(void *mlx, char *path);

// map_loader.c
void			count(t_map *map);
char			**get_map(char *argv, t_map *map);

// map_checker.c
int				check_shape(t_map *map);
int				check_wall(t_map *map);
int				check_other(t_map *map);

// flood_fill.c
int				validate_path(t_map *map);
// static char	**copy_map(char **data, int height);
// static void	fill(char **map, t_point size, t_point cur);

// render.c
void			draw_edge_corner(t_game *game, int x, int y);
void			draw_edge(t_game *game, int x, int y);
void			draw_walls(t_game *game, int x, int y);
void			draw_others(t_game *game, int x, int y);
void			render_map(t_game *game);

// input.c
int				key_hook(int keycode, t_game *game);

// utils.c
void			free_copy(char **copy);
int				close_window(t_game *game);
int				quit_game(t_game *game);

// move.c
int				check_moves(t_game *game, t_point new_pos);
void			display_moves(t_game *game);

//maelstrom.c
void			search_maelstrom(t_game *game);
void			move_maelstrom(t_game *game, int x, int y);
unsigned long	get_time(void);
int				loop_hook(t_game *game);

//Cette erreur vient de la MiniLibX (sous Linux), pas de ton code.
//Cela arrive car mlx_init() appelle XOpenDisplay, qui utilise une
//structure interne contenant des bytes non initialisés (bug de libX11).
//Ce n’est pas de ta faute. C’est un faux positif courant que 
//tu peux ignorer en toute sécurité, sauf si :
//Tu veux porter le projet sur Windows/macOS avec comportement 100 % 
//prévisible (ce qui n’est pas requis à 42),
//Tu veux une exécution 0-warning (dans ce cas, il faut patcher Xlib 
//— ce n’est pas recommandé ici).

#endif