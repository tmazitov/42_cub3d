/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 23:30:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/19 19:10:57 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h" 

int merge_hook(void *arg)
{
	t_game *game;

	game = (t_game *)arg;
	update_hook(game);
	render_hook(game);

	
    // int win_width = game->width;
    // int win_height = game->height;

    // // Center the cursor
	// //FOR MACOS
    // mlx_mouse_move(game->window, (win_width / 2), (win_height / 2));
	
	// //FOR LINUX 
    // // mlx_mouse_move(game->mlx, game->window, (win_width / 2), (win_height / 2));


	return (0);
}

int	close_game(void *param)
{
	t_game *game = (t_game *)param;
	free_game(game);
	exit(0);
	return (0);
}

// int test_hook(int keycode, t_game *game)
// {
// 	printf("release! %d\n", keycode);
// 	return (0);
// }


// #define FOCUSIN    (1 << 18) // Replace with correct value if available
// #define FOCUSINMASK (1 << 18)

// int recenter_cursor(void *param)
// {
// 	t_game *game = (t_game *)param;
// 	int x;
// 	int y;

// 	printf("recentering cursor\n");
// 	x = game->width / 2;
// 	y = game->height / 2;	
// 	mlx_mouse_hide(game->mlx);
// 	mlx_mouse_move(game->mlx, x, y);
// 	mlx_mouse_show(game->mlx);
// 	return (0);
// }

// int focus_event(void *param)
// {
//     t_game *game = (t_game *)param;
//     // Recenter cursor or perform other actions when window gains focus
//     recenter_cursor(game);
// 	return (0);
// }


// static int recenter_cursor(t_game *game)
// {
//     int win_width = game->width;
//     int win_height = game->height;

//     // Center the cursor
// 	//FOR MACOS
//     mlx_mouse_move(game->window, (win_width / 2), (win_height / 2));
	
// 	//FOR LINUX 
//     // mlx_mouse_move(game->mlx, game->window, (win_width / 2), (win_height / 2));

//     return 0;
// }


static void setup_game_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, merge_hook, game);

	// mlx_hook(game->mlx, recenter_cursor, game);

	
	//      trying to recenter mouse but UNSUCCESSFUL, due to error.
	// mlx_hook(game->mlx, FOCUSIN, FOCUSINMASK, focus_event, game); // Register focus event handler
	// mlx_loop_hook(game->mlx, recenter_cursor, game);
	

	// mlx_loop_hook(game->mlx, render_hook, game);
	// mlx_loop_hook(game->mlx, update_hook, game);
	// mlx_key_hook(game->window, key_hook, game);	
	// mlx_key_hook(game->window, player_control_hook, game);
	mlx_mouse_hook(game->window, player_mouse_control, game);
	mlx_hook(game->window, MouseMove, MouseMoveMask, player_mouse_move,  game->scene->player);
	mlx_hook(game->window, KeyPress, KeyPressMask, player_control_set, game->scene->player);
	mlx_hook(game->window, KeyRelease, KeyReleaseMask, player_control_unset, game->scene->player);	
	mlx_hook(game->window, 17, 1L << 17, close_game, game);
}

static void run(t_game *game)
{
	mlx_loop_hook(game->mlx, merge_hook, game);
	setup_game_hooks(game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (print_error("invalid count of args"), 1);
	srand(time(NULL)); 
	// game = make_game(argv[1], 1024, 600, "Hello world!");
	// game = make_game(argv[1], 720, 480, "Hello world!");
	// game = make_game(argv[1], 960, 640, "Hello world!");
	game = make_game(argv[1], 1440, 900, "Hello world!");
	// game = make_game(argv[1], 1920, 1080, "Hello world!");

	if (!game)
		return (1);
	run(game);
}
