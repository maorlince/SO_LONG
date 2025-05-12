/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:03:43 by manon             #+#    #+#             */
/*   Updated: 2025/05/12 18:53:28 by mlemerci         ###   ########.fr       */
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
	int	i;
	int	j;

	j = 0;
	while (game->map->data[j])
	{
		i = 0;
		while (game->map->data[j][i])
		{
			if (game->map->data[j][i] == 'P')
			{
				game->map->count_fisherman++;
				game->map->fisherman_pos.x = i;
				game->map->fisherman_pos.y = j;
			}
			else
				count_utils(game, game->map->data[j][i]);
			i++;
		}
		j++;
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
	free(map->stash);
	return (map->data);
}
