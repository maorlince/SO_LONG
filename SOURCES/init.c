/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:02:42 by manon             #+#    #+#             */
/*   Updated: 2025/05/03 19:44:22 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->data = NULL;
	map->width = 0;
	map->height = 0;
	map->count_fish = 0;
	map->count_exit = 0;
	map->count_fisherman = 0;
	map->count_maelstrom = 0;
	map->fisherman_pos.x = 0;
	map->fisherman_pos.y = 0;
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

static void	load_image(t_game *game, char *path, t_img *img)
{
	img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path,
			&img->width, &img->height);
	if (!img->ptr)
		ft_printf("⚠️ [Chargement de %s impossible\n]", path);
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
	load_image(game, IMG_MAELSTROM, &game->maelstrom);
	load_image(game, IMG_BRIDGE, &game->bridge);
	load_image(game, IMG_CORAL, &game->coral);
	load_image(game, IMG_EDGE1, &game->edge1);
	load_image(game, IMG_EDGE2, &game->edge2);
	load_image(game, IMG_EDGE3, &game->edge3);
	load_image(game, IMG_EDGE4, &game->edge4);
	load_image(game, IMG_EDGE_CORNER1, &game->edge_corner1);
	load_image(game, IMG_EDGE_CORNER2, &game->edge_corner2);
	load_image(game, IMG_EDGE_CORNER3, &game->edge_corner3);
	load_image(game, IMG_EDGE_CORNER4, &game->edge_corner4);
	load_image(game, IMG_WATER, &game->water);
	load_image(game, IMG_WAVES, &game->waves);
	game->moves = 0;
	return (1);
}
