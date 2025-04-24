/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:58:27 by manon             #+#    #+#             */
/*   Updated: 2025/04/23 15:08:57 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int check_args(int argc, char **argv)
{
	if (argc != 2)
		return (ft_printf("[Erreur : nombre d'arguments invalide]\n"), 0);
	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		return (ft_printf("[Erreur : map au nom invalide]\n"), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_args(argc, argv))
		return (1);
	game.map = init_map();
	if (!game.map)
		return (ft_printf("[Erreur : allocation map échouée]\n"));
	if (!get_map(argv[1], game.map))
		return (free_map(game.map), ft_printf("[Erreur : lecture échouée]\n"), 1);
	count(game.map);
	if (check_shape(game.map) || check_wall(game.map) || check_other(game.map))
		return (free_map(game.map), 1);
	if (!validate_path(game.map))
		return (free_map(game.map), ft_printf("[Erreur : map non jouable]\n"), 1);
	if (!init_images(&game))
		return (free_map(game.map), ft_printf("[Erreur : initialisation graphique]\n"), 1);
	render_map(&game);
	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_loop(game.mlx_ptr);
	free_map(game.map);
	return (0);
}
