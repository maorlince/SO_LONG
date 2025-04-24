/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:08:24 by manon             #+#    #+#             */
/*   Updated: 2025/04/24 18:54:08 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_copy(char **copy)
{
	int	i = 0;

	if (!copy)
		return ;
	while (copy[i])
		free(copy[i++]);
	free(copy);
}

#include "so_long.h"

int	close_window(t_game *game)
{
    free_map(game->map);
    mlx_destroy_window(game->mlx_ptr, game->win_ptr);
    exit(0);
    return (0);
}

