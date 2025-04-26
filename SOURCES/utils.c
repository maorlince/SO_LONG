/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:08:24 by manon             #+#    #+#             */
/*   Updated: 2025/04/26 14:46:18 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_copy(char **copy)
{
	int	i;

	i = 0;
	if (!copy)
		return ;
	while (copy[i])
		free(copy[i++]);
	free(copy);
}

int	close_window(t_game *game)
{
	free_map(game->map);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
	return (0);
}

void display_moves(t_game *game)
{
	char *number;
	char *str;

	number = ft_itoa(game->moves);
	str = ft_strjoin("Moves : ", number);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 10, 0xFFFFFF, str);
	free(number);
	free(str);
}

