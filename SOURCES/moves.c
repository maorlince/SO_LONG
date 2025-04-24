/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:07:56 by manon             #+#    #+#             */
/*   Updated: 2025/04/24 20:02:57 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//integrer dans le check?
void	print_moves(int moves)
{
	ft_printf("Moves: %d\n", moves);
}

int check_moves(t_game *game, t_point new_pos)
{
    char tile = game->map->data[new_pos.y][new_pos.x];
    if (tile == '1' || (tile == 'E' && game->map->count_fish != 0))
        return (0);
    if (tile == 'C')
        game->map->count_fish--;
    if (tile == 'E' && game->map->count_fish == 0)
		exit(0);// good end
    if (tile == 'S')
		exit(0);// bad end
    game->moves++;
    game->map->data[game->map->fisherman_pos.y][game->map->fisherman_pos.x] = '0';
    game->map->fisherman_pos = new_pos;
    game->map->data[new_pos.y][new_pos.x] = 'P';
    return (1);
}
