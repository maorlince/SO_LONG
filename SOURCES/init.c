/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:02:42 by manon             #+#    #+#             */
/*   Updated: 2025/04/23 16:05:01 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map *init_map(void)
{
    t_map *map = malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->data = NULL;
    map->width = 0;
    map->height = 0;
    map->count_fish = 0;
    map->count_exit = 0;
    map->count_fisherman = 0;
    map->count_sumo = 0;
    return (map);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map)
	{
		if (map->data)
		{
			while (map->data[i])
			{
				free(map->data[i]);
				i++;
			}
			free(map->data);
		}
		free(map);
	}
}

static void	*load_image(void *mlx, char *path)
{
	int	width;
	int	height;
	return (mlx_xpm_file_to_image(mlx, path, &width, &height));
}

int	init_images(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
	ft_printf("alloc map ok\n");
	game->win_ptr = mlx_new_window(game->mlx_ptr,
		game->map->width * IMG_SIZE,
		game->map->height * IMG_SIZE, "So_long");
	if (!game->win_ptr)
		return (0);
	ft_printf("alloc ptr size ok\n");
	game->img_fisherman = load_image(game->mlx_ptr, IMG_FISHERMAN);
	game->img_fish = load_image(game->mlx_ptr, IMG_FISH);
	game->img_sumo = load_image(game->mlx_ptr, IMG_SUMO);
	game->img_bridge = load_image(game->mlx_ptr, IMG_BRIDGE);
	game->img_coral = load_image(game->mlx_ptr, IMG_CORAL_1); // Ou aléatoire!!!!!!!
	game->img_edge = load_image(game->mlx_ptr, IMG_EDGE);
	game->img_edge_corner = load_image(game->mlx_ptr, IMG_EDGE_CORNER);
	game->img_water = load_image(game->mlx_ptr, IMG_WATER);
	if (!game->img_fisherman || !game->img_fish || !game->img_sumo ||
		!game->img_bridge || !game->img_coral || !game->img_edge ||
		!game->img_edge_corner || !game->img_water)
		return (0);
	ft_printf("alloc img ok\n");
	game->moves = 0;
	return (1);
}
