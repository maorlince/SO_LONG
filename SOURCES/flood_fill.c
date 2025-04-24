/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:05:31 by manon             #+#    #+#             */
/*   Updated: 2025/04/24 19:58:02 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**copy_map(char **data, int height)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (data[i])
	{
		copy[i] = ft_strdup(data[i]);
		if (!copy[i])
			return (NULL); // Pas clean
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	fill(char **map, t_point size, t_point cur)
{
	if (cur.x < 0 || cur.y < 0 || cur.x >= size.x || cur.y >= size.y)
		return;
	if (map[cur.y][cur.x] == '1' || map[cur.y][cur.x] == 'K')
		return;
	map[cur.y][cur.x] = 'K';
	fill(map, size, (t_point){cur.x + 1, cur.y});
	fill(map, size, (t_point){cur.x - 1, cur.y});
	fill(map, size, (t_point){cur.x, cur.y + 1});
	fill(map, size, (t_point){cur.x, cur.y - 1});
}

int	validate_path(t_map *map)
{
	char	**copy;
	int		y;
	int		x;

	copy = copy_map(map->data, map->height);
	if (!copy)
		return (0);
	fill(copy, (t_point){map->width, map->height}, map->fisherman_pos);
	y = 0;
	while (copy[y])
	{
		x = 0;
		while (copy[y][x])
		{
			if (copy[y][x] == 'C')
				return (free_copy(copy), 0);
			x++;
		}
		y++;
	}
	free_copy(copy);
	return (1);
}
