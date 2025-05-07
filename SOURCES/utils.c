/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:08:24 by manon             #+#    #+#             */
/*   Updated: 2025/05/07 15:47:14 by mlemerci         ###   ########.fr       */
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
	quit_game(game);
	return (1);
}

void	supp_edge(t_game *game)
{
	system("pkill mpg123");
	system("stty sane");
	if (game->edge_corner1.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge_corner1.ptr);
	if (game->edge_corner2.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge_corner2.ptr);
	if (game->edge_corner3.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge_corner3.ptr);
	if (game->edge_corner4.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge_corner4.ptr);
	if (game->edge1.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge1.ptr);
	if (game->edge2.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge2.ptr);
	if (game->edge3.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge3.ptr);
	if (game->edge4.ptr)
		mlx_destroy_image(game->mlx_ptr, game->edge4.ptr);
	if (game->black_tile.ptr)
		mlx_destroy_image(game->mlx_ptr, game->black_tile.ptr);
}

void	quit_game(t_game *game)
{
	if (game->map)
		free_map(game->map);
	supp_edge(game);
	if (game->coral.ptr)
		mlx_destroy_image(game->mlx_ptr, game->coral.ptr);
	if (game->water.ptr)
		mlx_destroy_image(game->mlx_ptr, game->water.ptr);
	if (game->waves.ptr)
		mlx_destroy_image(game->mlx_ptr, game->waves.ptr);
	if (game->fish.ptr)
		mlx_destroy_image(game->mlx_ptr, game->fish.ptr);
	if (game->bridge.ptr)
		mlx_destroy_image(game->mlx_ptr, game->bridge.ptr);
	if (game->fisherman.ptr)
		mlx_destroy_image(game->mlx_ptr, game->fisherman.ptr);
	if (game->maelstrom.ptr)
		mlx_destroy_image(game->mlx_ptr, game->maelstrom.ptr);
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(0);
}

void	song(t_game *game)
{
	if (game->lvl == '2' || game->lvl == '3')
		system("mpg123 --loop -1 -q musique1.mp3 &");
	else if (game->lvl == '4')
		system("mpg123 --loop -1 -q musique4.mp3 &");
	else if (game->lvl == '5')
		system("mpg123 --loop -1 -q musique3.mp3 &");
	else if (game->lvl == 'f')
		system("mpg123 --loop -1 -q musique2.mp3 &");
	else
		system("mpg123 --loop -1 -q musique5.mp3 &");
}
