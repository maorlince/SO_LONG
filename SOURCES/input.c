/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:07:27 by manon             #+#    #+#             */
/*   Updated: 2025/04/30 16:33:16 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int keycode, t_game *game)
{
	t_point			new_pos;

	if (keycode == KEY_ESC)
		close_window(game);
	game->held_key = keycode;
	new_pos = game->map->fisherman_pos;
	if ((keycode == KEY_W) || (keycode == KEY_UP))
		new_pos.y -= 1;
	else if ((keycode == KEY_S) || (keycode == KEY_DOWN))
		new_pos.y += 1;
	else if ((keycode == KEY_A) || (keycode == KEY_LEFT))
		new_pos.x -= 1;
	else if ((keycode == KEY_D) || (keycode == KEY_RIGHT))
		new_pos.x += 1;
	if (check_moves(game, new_pos) == 1)
	{
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		render_map(game);
	}
	return (0);
}
