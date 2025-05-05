/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:27:52 by manon             #+#    #+#             */
/*   Updated: 2025/05/05 12:30:41 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_black_tile(t_game *game)
{
	int		*data;
	int		x;
	int		y;
	int		size_line;

	game->black_tile.ptr = mlx_new_image(game->mlx_ptr, IMG_SIZE, IMG_SIZE);
	if (!game->black_tile.ptr)
		return ;
	data = (int *)mlx_get_data_addr(game->black_tile.ptr, &y,
			&size_line, &x);
	y = 0;
	while (y < IMG_SIZE)
	{
		x = 0;
		while (x < IMG_SIZE)
		{
			data[y * (size_line / 4) + x] = 0x000000;
			x++;
		}
		y++;
	}
}

void	draw_shadow(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->black_tile.ptr, x * IMG_SIZE, y * IMG_SIZE);
}

void	end_mode(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 450, 200, 0xFFFFFF,
		"On dirait bien que j'ai pecher tous les poissons du coin...");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 450, 275, 0xFFFFFF,
		"           Il est temps pour moi de rentrer.");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 500, 370, 0x00FF00,
		"               Merci.");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 500, 550, 0xFFFFFF,
		"               [q]");
}

void	dark_mode(t_game *game)
{
	if (!game->black_tile.ptr)
		init_black_tile(game);
	if (game->lvl == 'f')
		mlx_string_put(game->mlx_ptr, game->win_ptr, 390, 500,
			0xFF0000, "Do u want some 🌶️ ? [Y/y]");
	if (game->lvl == 'Y')
	{
		game->lvl = 'Z';
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		mlx_string_put(game->mlx_ptr, game->win_ptr, 300, 150,
			0xFF0000, "         Great...");
		mlx_string_put(game->mlx_ptr, game->win_ptr, 300, 250,
			0xFF0000, "   Good death Fisherman.");
		mlx_string_put(game->mlx_ptr, game->win_ptr, 300, 350,
			0xFF0000, "BWAHAHAHAHAHAHAHAHAHAHAHAHAHA");
		//usleep(1000000);
		//mlx_clear_window(game->mlx_ptr, game->win_ptr);
	}
	if (game->lvl == '7' && game->map->count_fish == 0)
	{
		end_mode(game);
		if (game->lvl == 'Q')
			game->lvl = '0';
		game->held_key = 0;
	}
}
