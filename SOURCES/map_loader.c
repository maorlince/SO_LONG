/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:03:43 by manon             #+#    #+#             */
/*   Updated: 2025/05/05 12:21:18 by manon            ###   ########.fr       */
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
	char	*stash;
	char	*tmp;
	char	*line;
	int		fd;

	stash = NULL;
	fd = open(argv, O_RDONLY);
	if (fd < 0 || !fd)
		return (ft_printf("⚠️ [Fichier map de taille invalide]\n"), NULL);
	line = get_next_line(fd);
	while (line)
	{
		tmp = stash;
		if (!stash)
			stash = ft_strdup(line);
		else
			stash = ft_strjoin(stash, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->data = ft_split(stash, '\n');
	free(stash);
	return (map->data);
}
