/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 23:30:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/30 20:16:50 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	merge_hook(void *arg)
{
	t_game	*game;

	game = (t_game *)arg;
	update_hook(game);
	if (game->scene->player->finish_game)
	{
		free_game(game);
		exit(0);
	}
	render_hook(game);
	return (0);
}

int	close_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	exit(0);
	return (0);
}

static void	setup_game_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, merge_hook, game);
	mlx_mouse_hook(game->window, player_mouse_control, game);
	mlx_hook(game->window, MOUSE_MOVE, 1L << 6, player_mouse_move,
		game->scene->player);
	mlx_hook(game->window, KEY_PRESS, 1L << 0, player_control_set,
		game->scene->player);
	mlx_hook(game->window, KEY_RELEASE, 1L << 1, player_control_unset,
		game->scene->player);
	mlx_hook(game->window, 17, 1L << 17, close_game, game);
}

static	int	check_argv_cub(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i < 5)
		return (print_error("invalid file name"), 1);
	if (argv[i - 1] != 'b' || argv[i - 2] != 'u'
		|| argv[i - 3] != 'c' || argv[i - 4] != '.')
		return (print_error("invalid file extension"), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;
	int		width;
	int		height;

	if (argc != 2)
		return (print_error("invalid count of args"), 1);
	if (check_argv_cub(argv[1]))
		return (1);
	srand(time(NULL));
	width = 1440;
	height = 900;
	game = make_game(argv[1], width, height, "Call of Coder!");
	ambient_sound(game, "cub3d_ambient_game_sound.wav");
	if (!game)
		return (1);
	mlx_loop_hook(game->mlx, merge_hook, game);
	setup_game_hooks(game);
	mlx_loop(game->mlx);
}
