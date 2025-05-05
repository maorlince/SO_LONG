/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:07:56 by manon             #+#    #+#             */
/*   Updated: 2025/05/05 16:58:30 by manon            ###   ########.fr       */
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
	game->map->data[game->map->fisherman_pos.y]
	[game->map->fisherman_pos.x] = '0';
	if (&game->map->fisherman_pos != &new_pos)
		game->moves++;
	game->map->fisherman_pos = new_pos;
	game->map->data[new_pos.y][new_pos.x] = 'P';
	return (1);
}

void	display_moves(t_game *game)
{
	char	*number;
	char	*str;

	number = ft_itoa(game->moves);
	str = ft_strjoin("Moves : ", number);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 50, 13, 0xFFFFFF, str);
	free(number);
	free(str);
}
