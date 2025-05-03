/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maelstrom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:27:06 by manon             #+#    #+#             */
/*   Updated: 2025/05/03 18:17:32 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	search_maelstrom(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (game->map->data[y])
	{
		x = 0;
		while (game->map->data[y][x])
		{
			if (game->map->data[y][x] == MAELSTROM)
			{
				move_maelstrom(game, x, y);
				count++;
				if (count == game->map->count_maelstrom)
					return ;
			}
			x++;
		}
		y++;
	}
}

void	move_maelstrom(t_game *game, int x, int y)
{
	t_point	try_pos;
	int		alea;
	int		new_x;
	int		new_y;

	alea = rand() % 4;
	try_pos = game->add_pos[alea];
	new_x = x + try_pos.x;
	new_y = y + try_pos.y;
	if (new_x < 0 || new_y < 0 || new_y >= game->map->height
		|| new_x >= (int)ft_strlen(game->map->data[new_y]))
		return ;
	if (game->map->data[new_y][new_x] == WATER)
	{
		game->map->data[y][x] = WATER;
		game->map->data[new_y][new_x] = MAELSTROM;
	}
	else if (game->map->data[new_y][new_x] == PLAYER)
	{
		ft_printf("[GAME OVER] 🌀\n");
		quit_game(game);
	}
	return ;
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	loop_hook(t_game *game)
{
	unsigned long	current;

	current = get_time();
	if (current - game->last_update >= 500)
	{
		game->water_frame++;
		search_maelstrom(game);
		render_map(game);
		game->last_update = current;
		if (game->held_key)
			key_hook(game->held_key, game);
	}
	return (0);
}
