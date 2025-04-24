/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:20:02 by manon             #+#    #+#             */
/*   Updated: 2025/04/20 20:20:38 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// ajouter bateau tournant selon direction 
// ponton selon bord
// bord selon bord
// sumo
// coraux
// message sortie
// bloquer sortie si pas tous les poissons

t_map *init_map(void)
{
    t_map *map = malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->data = NULL;
    map->width = 0;
    map->height = 0;
    map->count_fish = 0;
    map->count_exit = 0;
    map->count_fisherman = 0;
    map->count_sumo = 0;
    return (map);
}


void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map)
	{
		if (map->data)
		{
			while (map->data[i])
			{
				free(map->data[i]);
				i++;
			}
			free(map->data);
		}
		free(map);
	}
}

char **get_map(char *argv, t_map *map)
{
	char *stash;
	char *tmp;
	char *line;
	int fd;

	stash = NULL;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (NULL);
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

int check_shape(t_map *map)
{
	int i;
	int j;
	int	size_line;

	j = 0;
	size_line = 0;
	while(map->data[j])
	{
		i = 0;
		while(map->data[j][i])
			i++;
		if(size_line == 0)
			size_line = i;
		if (size_line != i || size_line == 0)
			return(ft_printf("[Erreur : map de taille invalide]\n"));
		j++;
	}
	map->width = size_line;
	map->height = j;
	return (0);
}

int check_wall(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map->data[0][i])
	{
		if (map->data[0][i] != '1'
			|| map->data[map->height - 1][i] != '1')
			return (ft_printf("[Erreur : map avec murs invalides]\n"));
		i++;
	}
	i = 0;
	while (map->data[j])
	{
		if (map->data[j][0] != '1'
			|| map->data[j][map->width - 1] != '1')
			return (ft_printf("[Erreur : map avec murs invalides]\n"));
		j++;
	}
	return (0);
}

int	check_other(t_map *map)
{
	if (map->count_fish < 1)
		return(ft_printf("[Erreur : map avec collectibles invalides]\n"));
	if (map->count_exit != 1)
		return(ft_printf("[Erreur : map avec sortie invalide]\n"));
	if (map->count_fisherman != 1)
		return(ft_printf("[Erreur : map avec nombre de pêcheurs invalide]\n"));
	return (0);
}

void	fill(char **map_tmp, t_point size, t_point current, char value_wanted)
{
	if ((current.y < 0) || (current.x < 0) || (current.y >= size.y)
		|| (current.x >= size.x) || map_tmp[current.y][current.x] != value_wanted)
		return ;
	if (map_tmp[current.y][current.x] == 'E')
        return;
	map_tmp[current.y][current.x] = 'K';
	fill(map_tmp, size, (t_point){current.x - 1, current.y}, value_wanted);
	fill(map_tmp, size, (t_point){current.x + 1, current.y}, value_wanted);
	fill(map_tmp, size, (t_point){current.x, current.y - 1}, value_wanted);
	fill(map_tmp, size, (t_point){current.x, current.y + 1}, value_wanted);
}

int main(int argc, char **argv)
{
	t_map *map;
	t_point	size;
	t_point	start;

    if (argc != 2)
            return(ft_printf("[Erreur : nombre d'arguments invalide]\n"));
    if (ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])) == NULL)
		return(ft_printf("[Erreur : map au nom invalide]\n"));
	map = init_map();
	if (map == NULL)
		return (free_map(map), ft_printf("[Erreur : allocation map échouée]\n"));
	if (!get_map(argv[1], map))
		return(free_map(map), 1);
	count(map);
	if (check_shape(map))
		return(free_map(map), 1);
	if (check_wall(map))
		return(free_map(map), 1);
	if (check_other(map))
		return(free_map(map), 1);

	size.x = map->width;
	size.y = map->height;
	start = map->fisherman_pos;
	fill(map->data, size, start, '0');
	free_map(map);
}
