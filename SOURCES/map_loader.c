/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:03:43 by manon             #+#    #+#             */
/*   Updated: 2025/05/07 16:11:54 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->data[j])
	{
		i = 0;
		while (map->data[j][i])
		{
			if (map->data[j][i] == 'C')
				map->count_fish++;
			if (map->data[j][i] == 'E')
				map->count_exit++;
			if (map->data[j][i] == 'P')
			{
				map->count_fisherman++;
				map->fisherman_pos.x = i;
				map->fisherman_pos.y = j;
			}
			if (map->data[j][i] == 'S')
				map->count_maelstrom++;
			i++;
		}
		j++;
	}
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
	while(map->line)
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
