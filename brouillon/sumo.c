/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sumo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:27:06 by manon             #+#    #+#             */
/*   Updated: 2025/04/24 20:10:34 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void search_sumos(t_game *game)
{
    int i;
    int j;

    j = 0;
    while (game->map->data[j][i])
    {
        i = 0;
        while (game->map->data[j][i] != 'S' && game->map->data[j][i])
            i++;
        if (game->map->data[j][i] == 'S')

            j++;
    }
}

void move_sumos(t_game *game)
{
    int i;
    int j;
    t_point new_pos;
    
    while (game->map->data[j][i++] == WATER)
    {
        new_pos.x = i;
        new_pos.y = j;
        sleep(1);
    }
    while (game->map->data[j++][i] == WATER)
    {
        new_pos.x = i;
        new_pos.y = j;
        sleep(1);
    }
    while (game->map->data[j][i--] == WATER)
    {
        new_pos.x = i;
        new_pos.y = j;
        sleep(1);
    }
    while (game->map->data[j--][i] == WATER)
    {
        new_pos.x = i;
        new_pos.y = j;
        sleep(1);
    }
    game->map->data[j][i] = WATER;
    game->map->data[new_pos.y][new_pos.x] = SUMO;
}
// Exemple d'utilisation dans boucle principale MLX
int loop_hook(t_game *game)
{
    search_sumos(game);
    move_sumos(game);
    return (0);
}
