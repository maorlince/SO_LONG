/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:06:33 by manon             #+#    #+#             */
/*   Updated: 2025/04/30 14:59:44 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_edge_corner(t_game *game, int x, int y)
{
	if (y == 0 && x == 0)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge_corner1.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (y == 0 && x == game->map->width - 1)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge_corner2.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (y == game->map->height - 1 && x == 0)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge_corner3.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (y == game->map->height - 1 && x == game->map->width - 1)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge_corner4.ptr, x * IMG_SIZE, y * IMG_SIZE);
}

void	draw_edge(t_game *game, int x, int y)
{
	if (y == 0)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge1.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (y == game->map->height - 1)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge2.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (x == 0)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge3.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if ( x == game->map->width - 1)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->edge4.ptr, x * IMG_SIZE, y * IMG_SIZE);
}

void	draw_walls(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map->data[y][x];
	if (tile == WALL)
	{
		if ((y == 0 && x == 0) || (y == 0 && x == game->map->width - 1)
			|| (y == game->map->height - 1 && x == 0)
			|| (y == game->map->height - 1 && x == game->map->width - 1))
			draw_edge_corner(game, x, y);
		else if (y == 0 || y == game->map->height - 1
			|| x == 0 || x == game->map->width - 1)
			draw_edge(game, x, y);
		else
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->coral.ptr, x * IMG_SIZE, y * IMG_SIZE);
	}
	else
		draw_others(game, x, y);
}

void	draw_others(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map->data[y][x];
	if (tile == WATER)
	{
		if (game->water_frame % 2 == 0)
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->water.ptr, x * IMG_SIZE, y * IMG_SIZE);
		else
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->waves.ptr, x * IMG_SIZE, y * IMG_SIZE);
	}
	else if (tile == FISH)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->fish.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == EXIT)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->bridge.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == PLAYER)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->fisherman.ptr, x * IMG_SIZE, y * IMG_SIZE);
	else if (tile == MAELSTROM)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			game->maelstrom.ptr, x * IMG_SIZE, y * IMG_SIZE);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	if(!game->water_frame || game->water_frame == 1024)
		game->water_frame = 1;
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
	display_moves(game);
}