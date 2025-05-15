/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:03:43 by manon             #+#    #+#             */
/*   Updated: 2025/05/14 18:19:48 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	count_utils(t_game *game, char data)
{
	if (data == 'C')
		game->map->count_fish++;
	else if (data == 'E')
		game->map->count_exit++;
	else if (data == 'S')
		game->map->count_maelstrom++;
	else if (data != '0' && data != '1')
	{
		(ft_printf("⚠️ [Caractere invalide dans la map]\n"));
		quit_game(game);
	}
}

int	count(t_game *game)
{
	t_point	pos;

	pos.x = 0;
	pos.y = 0;
	while (game->map->data[pos.y])
	{
		pos.x = 0;
		while (game->map->data[pos.y][pos.x])
		{
			if (game->map->data[pos.y][pos.x] == 'P')
			{
				game->map->count_fisherman++;
				game->map->fisherman_pos = pos;
			}
			else
				count_utils(game, game->map->data[pos.y][pos.x]);
			if (game->map->data[pos.y][pos.x] == 'E')
				game->map->bridge_pos = pos;
			pos.x++;
		}
		pos.y++;
	}
	return (0);
}

char	**get_map(char *argv, t_map *map)
{
	int		fd;

	map->stash = NULL;
	fd = open(argv, O_RDONLY);
	if (fd <= 0 || !fd)
		return (ft_printf("⚠️ [Fichier map de taille invalide]\n"), NULL);
	map->line = get_next_line(fd);
	if (map->line == NULL)
		return (ft_printf("⚠️ [Fichier map vide]\n"), NULL);
	while (map->line)
	{
		if (map->line[0] == '\n')
			return (ft_printf("⚠️ [Ligne vide dans le fichier map]\n"), NULL);
		map->tmp = map->stash;
		if (!map->stash)
		map->stash = ft_strdup(map->line);
		else
		map->stash = ft_strjoin(map->stash, map->line);
		free(map->tmp);
		free(map->line);
		map->line = get_next_line(fd);
	}
	close(fd);
	map->data = ft_split(map->stash, '\n');
	return (free(map->stash), map->data);
}
