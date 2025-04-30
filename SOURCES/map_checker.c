/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:04:41 by manon             #+#    #+#             */
/*   Updated: 2025/04/30 15:11:03 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_shape(t_map *map)
{
	int	i;
	int	j;
	int	size_line;

	j = 0;
	size_line = 0;
	while (map->data[j])
	{
		i = 0;
		while (map->data[j][i])
			i++;
		if (size_line == 0)
			size_line = i;
		if (size_line != i || size_line == 0)
			return (ft_printf("⚠️ [Map de taille/forme invalide]\n"));
		j++;
		if (i > 35 || j > 25)
			return (ft_printf("⚠️ [Map de taille trop importante]\n"));
	}
	map->width = size_line;
	map->height = j;
	return (0);
}

int	check_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->data[0][i])
	{
		if (map->data[0][i] != '1'
			|| map->data[map->height - 1][i] != '1')
			return (ft_printf("⚠️ [Map avec murs invalides]\n"));
		i++;
	}
	i = 0;
	while (map->data[j])
	{
		if (map->data[j][0] != '1'
			|| map->data[j][map->width - 1] != '1')
			return (ft_printf("⚠️ [Map avec murs invalides]\n"));
		j++;
	}
	return (0);
}

int	check_other(t_map *map)
{
	if (map->count_fish < 1)
		return (ft_printf("⚠️ [Map avec nombre de collectibles invalides]\n"));
	if (map->count_exit != 1)
		return (ft_printf("⚠️ [Map avec nombre de sortie invalide]\n"));
	if (map->count_fisherman != 1)
		return (ft_printf("⚠️ [Map avec nombre de pêcheurs invalide]\n"));
	return (0);
}
