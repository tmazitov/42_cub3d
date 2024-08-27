/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 23:30:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 20:12:40 by kshamsid         ###   ########.fr       */
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

// #include "../miniaudio/miniaudio.h"
#include <stdio.h>

typedef struct s_ambient_sound
{
	t_game	*game;
	char	*sound_path;
}		t_ambient_sound;

void	*ambient_sound_func(void *arg)
{
	t_ambient_sound	*ambient_sound;
	char			*sound_path;
	ma_result		result;
	ma_engine		engine;

	ambient_sound = (t_ambient_sound *)arg;
	sound_path = ambient_sound->sound_path;

	// Initialize the engine
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS) {
		printf("Failed to initialize audio engine.\n");
		return (NULL);
	}

	// Play the sound
	result = ma_engine_play_sound(&engine, sound_path, NULL);
	if (result != MA_SUCCESS) {
		printf("Failed to play sound.\n");
		ma_engine_uninit(&engine);
		return (NULL);
	}

	// Wait until the sound finishes playing
	while (1)
	{
		if (ambient_sound->game->blocker == 1)
			break ;
		usleep(500000);
	}
	ma_engine_uninit(&engine);
	// Clean up
	return (NULL);
}

void	ambient_sound(t_game *game, char *sound_path)
{
	t_ambient_sound	*ambient_sound;
	pthread_t		sound_thread;

	ambient_sound = malloc(sizeof(t_ambient_sound));
	ambient_sound->game = game;
	ambient_sound->sound_path = sound_path;
	pthread_create(&sound_thread, NULL, ambient_sound_func, ambient_sound);
	pthread_detach(sound_thread);
}

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
	ambient_sound(game, "cub3d_ambient_game_sound.wav");
	// game = make_game(argv[1], 1920, 1080, "Hello world!");
	if (!game)
		return (1);
	run(game);
}
