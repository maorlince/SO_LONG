/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:03:43 by manon             #+#    #+#             */
/*   Updated: 2025/04/23 15:06:55 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void count(t_map *map)
{
	int i = 0;
	int j; 
	
	j = 0;
	while(map->data[j])
	{
		i = 0;
		while(map->data[j][i])
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
			map->count_sumo++;
			i++;
		}
		j++;
	}
}
//pour get_map
//À séparer :
//lecture (read_map_file.c)
//split et parsing (parse_map.c)
//et aussi vérifier les erreurs de ft_strdup, ft_strjoin, get_next_line.
//renvoyer une erreur explicite (NULL ou code erreur).
char **get_map(char *argv, t_map *map)
{
	char *stash;
	char *tmp;
	char *line;
	int fd;

	stash = NULL;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (ft_printf("[Erreur : fichier map vide]"), NULL);
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
