/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:42:36 by manon             #+#    #+#             */
/*   Updated: 2025/04/21 16:56:45 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define IMG_SIZE 128

void render_map(t_game *game)
{
    int x;
	int y;

    y = 0;
    while (game->map->data[y])
    {
        x = 0;
        while (game->map->data[y][x])
        {
            if (game->map->data[y][x] == '1')
			{
				if ((y == 0 && x == 0) || (y == 0 && x == game->map->width - 1) ||
				(y == game->map->height - 1 && x == 0) || 
				(y == game->map->height - 1 && x == game->map->width - 1))
					mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                    	game->img_edge_corner, x * IMG_SIZE, y * IMG_SIZE);
				else if (y == 0 || y == game->map->height - 1 || x == 0 ||
					 x == game->map->width - 1)
					mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
						game->img_edge, x * IMG_SIZE, y * IMG_SIZE);
				else 
					mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
						game->img_coral, x * IMG_SIZE, y * IMG_SIZE);
			}
            else if (game->map->data[y][x] == '0')
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                    game->img_water, x * IMG_SIZE, y * IMG_SIZE);
            else if (game->map->data[y][x] == 'C')
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                    game->img_fish, x * IMG_SIZE, y * IMG_SIZE);
            else if (game->map->data[y][x] == 'E')
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                    game->img_bridge, x * IMG_SIZE, y * IMG_SIZE);
            else if (game->map->data[y][x] == 'P')
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                    game->img_fisherman, x * IMG_SIZE, y * IMG_SIZE);
			else if (game->map->data[y][x] == 'S')
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
                    game->img_sumo, x * IMG_SIZE, y * IMG_SIZE);
            x++;
        }
        y++;
    }
}

int key_hook(int keycode, t_game *game)
{
	t_point new_pos;

    if (keycode == KEY_ESC)
        exit(0);
    new_pos = game->map->fisherman_pos;
    if ((keycode == KEY_W) || (keycode == KEY_UP))
        new_pos.y -= 1;
    else if ((keycode == KEY_S) || (keycode == KEY_DOWN))
        new_pos.y += 1;
    else if ((keycode == KEY_A) || (keycode == KEY_LEFT))
        new_pos.x -= 1;
    else if ((keycode == KEY_D) || (keycode == KEY_RIGHT))
        new_pos.x += 1;
    
    if (check_moves(game, new_pos) == 1)
    {
        mlx_clear_window(game->mlx_ptr, game->win_ptr);
        render_map(game);
    }
    return (0);
}

int check_moves(t_game *game, t_point new_pos)
{
    char tile = game->map->data[new_pos.y][new_pos.x];
    if (tile == '1')
        return (0);
    if (tile == 'C')
        game->map->count_fish--;
    if (tile == 'E' && game->map->count_fish == 0)
		exit(0);// good end
    if (tile == 'S')
		exit(0);// bad end
    game->moves++;
    game->map->data[game->map->fisherman_pos.y][game->map->fisherman_pos.x] = '0';
    game->map->fisherman_pos = new_pos;
    game->map->data[new_pos.y][new_pos.x] = 'P';
    return (1);
}

int main(int argc, char **argv)
{
    t_game  game;
    int     img_width;
	int 	img_height;
    int     i;
	int		j;

    if (argc != 2)
        return (ft_printf("[Erreur : nombre d'arguments invalide]\n"), 1);
    if (ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])) == NULL)
        return (ft_printf("[Erreur : map au nom invalide]\n"), 1);

    game.map = init_map();
    if (game.map == NULL)
        return (ft_printf("[Erreur : allocation map échouée]\n"));
    if (!get_map(argv[1], game.map))
        return (free_map(game.map), ft_printf("[Erreur : lecture de map échouée]\n"), 1);
    count(game.map);
    if (check_shape(game.map))
        return (free_map(game.map), 1);
    if (check_wall(game.map))
        return (free_map(game.map), 1);
    if (check_other(game.map))
        return (free_map(game.map), 1);

    game.mlx_ptr = mlx_init();
    if (!game.mlx_ptr)
        return (free_map(game.map), ft_printf("[Erreur : mlx_init échoué]\n"), 1);
    game.win_ptr = mlx_new_window(game.mlx_ptr, game.map->width * IMG_SIZE,
                                    game.map->height * IMG_SIZE, "So_long");
	
    game.img_coral = mlx_xpm_file_to_image(game.mlx_ptr, "images/coral.xpm", &img_width, &img_height);
    game.img_edge = mlx_xpm_file_to_image(game.mlx_ptr, "images/edge.xpm", &img_width, &img_height);
	game.img_edge_corner = mlx_xpm_file_to_image(game.mlx_ptr, "images/edge_corner.xpm", &img_width, &img_height);
    game.img_water = mlx_xpm_file_to_image(game.mlx_ptr, "images/water.xpm", &img_width, &img_height);
    game.img_fish = mlx_xpm_file_to_image(game.mlx_ptr, "images/fish.xpm", &img_width, &img_height);
    game.img_bridge = mlx_xpm_file_to_image(game.mlx_ptr, "images/bridge.xpm", &img_width, &img_height);
    game.img_sumo = mlx_xpm_file_to_image(game.mlx_ptr, "images/sumo.xpm", &img_width, &img_height);
	game.img_fisherman = mlx_xpm_file_to_image(game.mlx_ptr, "images/fisherman.xpm", &img_width, &img_height);

    j = 0;
    while (game.map->data[j])
    {
        i = 0;
        while (game.map->data[j][i])
        {
            if (game.map->data[j][i] == 'P')
            {
                game.map->fisherman_pos.x = i;
                game.map->fisherman_pos.y = j;
            }
            i++;
        }
        j++;
    }
    render_map(&game);
    mlx_key_hook(game.win_ptr, key_hook, &game);
    mlx_loop(game.mlx_ptr);
    free_map(game.map);
    return (0);
}