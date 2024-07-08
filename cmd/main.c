/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 23:30:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/08 15:44:20 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h" 

int merge_hook(void *game)
{
	update_hook(game);
	render_hook(game);
	return (0);
}

int test_hook(int keycode, t_game *game)
{
	printf("release! %d\n", keycode);
	return (0);
}

static void setup_game_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, merge_hook, game);
	// mlx_loop_hook(game->mlx, render_hook, game);
	// mlx_loop_hook(game->mlx, update_hook, game);
	// mlx_key_hook(game->window, key_hook, game);	
	// mlx_key_hook(game->window, player_control_hook, game);
		
	mlx_hook(game->window, KeyPress, KeyPressMask, player_control_set, game->scene->player);
	mlx_hook(game->window, KeyRelease, KeyReleaseMask, player_control_unset, game->scene->player);	
	// mlx_hook(game->window, 17, 1L << 17, close_game, game);
}

static void run(t_game *game)
{
	setup_game_hooks(game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	*game;
	void	*mlx;
	void	*mlx_win;
	
	if (argc != 2)
		return (print_error("invalid count of args"), 1);
	game = make_game(argv[1], 1920, 1080, "Hello world!");
	if (!game)
		return (1);
	run(game);
}