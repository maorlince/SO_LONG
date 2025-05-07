/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:58:27 by manon             #+#    #+#             */
/*   Updated: 2025/05/07 16:01:52 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_args(int argc, char **argv, t_game *game)
{
	int	i;

	i = 0;
	game->lvl = '0';
	if (argc != 2)
		return (ft_printf("⚠️ [Nombre d'arguments invalide]\n"), 0);
	while (argv[1][i])
	{
		if (argv[1][i] > '0' && argv[1][i] < '9')
			game->lvl = argv[1][i];
		i++;
		if (argv[1][i] == 'f')
			game->lvl = argv[1][i];
	}
	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
		return (ft_printf("⚠️ [Nom de map invalide]\n"), 0);
	return (1);
}

static void	init_struct_attributes(t_game *game)
{
	game->moves = 0;
	game->held_key = 0;
	game->water_frame = 0;
	game->mlx_ptr = 0;
	game->win_ptr = 0;
	game->last_update = 0;
	ft_bzero(&game->edge1, sizeof(t_img));
	ft_bzero(&game->edge2, sizeof(t_img));
	ft_bzero(&game->edge3, sizeof(t_img));
	ft_bzero(&game->edge4, sizeof(t_img));
	ft_bzero(&game->edge_corner1, sizeof(t_img));
	ft_bzero(&game->edge_corner2, sizeof(t_img));
	ft_bzero(&game->edge_corner3, sizeof(t_img));
	ft_bzero(&game->edge_corner4, sizeof(t_img));
	ft_bzero(&game->coral, sizeof(t_img));
	ft_bzero(&game->water, sizeof(t_img));
	ft_bzero(&game->waves, sizeof(t_img));
	ft_bzero(&game->fish, sizeof(t_img));
	ft_bzero(&game->bridge, sizeof(t_img));
	ft_bzero(&game->fisherman, sizeof(t_img));
	ft_bzero(&game->maelstrom, sizeof(t_img));
	ft_bzero(&game->black_tile, sizeof(t_img));
}

void	init_add_pos(t_game *game)
{
	game->add_pos[0].x = 1;
	game->add_pos[0].y = 0;
	game->add_pos[1].x = 0;
	game->add_pos[1].y = 1;
	game->add_pos[2].x = -1;
	game->add_pos[2].y = 0;
	game->add_pos[3].x = 0;
	game->add_pos[3].y = -1;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_args(argc, argv, &game))
		exit(1);
	init_add_pos(&game);
	init_struct_attributes(&game);
	game.last_update = 0;
	game.map = init_map();
	if (!game.map)
		return (ft_printf("⚠️ [Allocation map échouée]\n"));
	if (!get_map(argv[1], game.map))
		quit_game(&game);
	count(game.map);
	if (check_shape(game.map) || check_wall(game.map) || check_other(game.map))
		return (free_map(game.map), 1);
	if (!validate_path(game.map))
		return (free_map(game.map), ft_printf("⚠️ [Map non jouable]\n"), 1);
	if (!init_images(&game))
		return (free_map(game.map), ft_printf("⚠️ [Initialisa° images]\n"), 1);
	render_map(&game);
	mlx_key_hook(game.win_ptr, key_hook, &game);
	mlx_hook(game.win_ptr, 17, 0L, close_window, &game);
	mlx_loop_hook(game.mlx_ptr, loop_hook, &game);
	mlx_loop(game.mlx_ptr);
	free_map(game.map);
}
