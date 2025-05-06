/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:07:27 by manon             #+#    #+#             */
/*   Updated: 2025/05/06 17:13:19 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int keycode, t_game *game)
{
	t_point			new_pos;

	if (keycode == KEY_ESC)
		quit_game(game);
	game->held_key = keycode;
	new_pos = game->map->fisherman_pos;
	if (keycode == KEY_YY || keycode == KEY_Y)
		game->lvl = 'Y';
	else if (keycode == KEY_QQ || keycode == KEY_Q)
		game->lvl = 'Q';
	else if ((keycode == KEY_W) || (keycode == KEY_UP))
		new_pos.y -= 1;
	else if ((keycode == KEY_S) || (keycode == KEY_DOWN))
		new_pos.y += 1;
	else if ((keycode == KEY_A) || (keycode == KEY_LEFT))
		new_pos.x -= 1;
	else if ((keycode == KEY_D) || (keycode == KEY_RIGHT))
		new_pos.x += 1;
	if (check_moves(game, new_pos))
	{
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		render_map(game);
	}
	return (0);
}
