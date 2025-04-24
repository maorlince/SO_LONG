/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:06:33 by manon             #+#    #+#             */
/*   Updated: 2025/04/21 17:40:46 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//void put_tile(t_game *game, char tile, int x, int y); (optionnel pour découper)

void	draw_walls(t_game *game, int x, int y)
{
	char tile = game->map->data[y][x];

	if (tile == WALL)
	{
		if ((y == 0 && x == 0) || (y == 0 && x == game->map->width - 1) ||
			(y == game->map->height - 1 && x == 0) ||
			(y == game->map->height - 1 && x == game->map->width - 1))
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img_edge_corner, x * IMG_SIZE, y * IMG_SIZE);
		else if (y == 0 || y == game->map->height - 1 || 
			x == 0 || x == game->map->width - 1)
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img_edge, x * IMG_SIZE, y * IMG_SIZE);
		else
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img_coral, x * IMG_SIZE, y * IMG_SIZE);
	}
	else
		draw_others(game, x, y);
}
void	draw_others(t_game *game, int x, int y)
{
	char tile = game->map->data[y][x];

	if (tile == WATER)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->img_water, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == FISH)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->img_fish, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == EXIT)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->img_bridge, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == PLAYER)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->img_fisherman, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == SUMO)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->img_sumo, x * IMG_SIZE, y * IMG_SIZE);
}


void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map->data[y])
	{
		x = 0;
		while (game->map->data[y][x])
		{
			draw_walls(game, x, y);
			x++;
		}
		y++;
	}
}
