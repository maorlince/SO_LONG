/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:02:42 by manon             #+#    #+#             */
/*   Updated: 2025/04/24 21:15:41 by mlemerci         ###   ########.fr       */
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

static void	load_image(t_game *game,char *path, t_img *img)
{
	img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->width, &img->height);
	if(!img->ptr)
		ft_printf("[Erreur cannot load: %s\n]", path);
}


int	init_images(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
		game->map->width * IMG_SIZE,
		game->map->height * IMG_SIZE, "So_long");
	if (!game->win_ptr)
		return (0);
	load_image(game, IMG_FISHERMAN, &game->fisherman);
	load_image(game, IMG_FISH, &game->fish);
	load_image(game, IMG_SUMO, &game->sumo);
	load_image(game, IMG_BRIDGE, &game->bridge);
	load_image(game, IMG_CORAL, &game->coral);
	load_image(game, IMG_EDGE, &game->edge);
	load_image(game, IMG_EDGE_CORNER, &game->edge_corner);
	load_image(game, IMG_WATER, &game->water);
	game->moves = 0;
	return (1);
}
