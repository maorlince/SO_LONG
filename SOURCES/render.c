/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:06:33 by manon             #+#    #+#             */
/*   Updated: 2025/04/24 21:08:52 by mlemerci         ###   ########.fr       */
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
				game->edge_corner.ptr, x * IMG_SIZE, y * IMG_SIZE);
		else if (y == 0 || y == game->map->height - 1 || 
			x == 0 || x == game->map->width - 1)
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->edge.ptr, x * IMG_SIZE, y * IMG_SIZE);
		else
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->coral.ptr, x * IMG_SIZE, y * IMG_SIZE);
	}
	else
		draw_others(game, x, y);
}
void	draw_others(t_game *game, int x, int y)
{
	// pixel = ARGB(0xFF FF FF FF)
	char tile = game->map->data[y][x];

	if (tile == WATER)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->water.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == FISH)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->fish.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == EXIT)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->bridge.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == PLAYER)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->fisherman.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == SUMO)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->sumo.ptr, x * IMG_SIZE, y * IMG_SIZE);
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
