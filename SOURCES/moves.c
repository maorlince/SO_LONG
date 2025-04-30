/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:07:56 by manon             #+#    #+#             */
/*   Updated: 2025/04/30 15:28:20 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_moves(t_game *game, t_point new_pos)
{
	char	tile;

	tile = game->map->data[new_pos.y][new_pos.x];
	if (tile == '1' || (tile == 'E' && game->map->count_fish != 0))
		return (0);
	if (tile == 'C')
		game->map->count_fish--;
	if (tile == 'E' && game->map->count_fish == 0)
	{
		ft_printf("[STAGE FINISH] 🎣\n");
		quit_game(game);
	}	
	if (tile == 'S')
	{
		ft_printf("[GAME OVER] 🌀\n");
		quit_game(game);
	}
	game->moves++;
	game->map->data[game->map->fisherman_pos.y]
	[game->map->fisherman_pos.x] = '0';
	game->map->fisherman_pos = new_pos;
	game->map->data[new_pos.y][new_pos.x] = 'P';
	return (1);
}
