/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control_mouse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 01:47:25 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/13 17:48:14 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

#define MINIAUDIO_IMPLEMENTATION
// #include "./miniaudio/miniaudio.h"

#include "../../miniaudio/miniaudio.h"
#include <stdio.h>

// int main(void)
void	*shoot_sound_func(void *arg)
{

	char *sound_path;

	sound_path = (char *)arg;
    ma_result result;
    ma_engine engine;

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
	usleep(1000000);

    ma_engine_uninit(&engine);
    // Clean up
	return (NULL);
}


int	player_mouse_scroll(int button, int x, int y, t_game *game)
{
	(void)x;
    (void)y;
	t_player *player;

	player = game->scene->player;
	if (button == LEFT_CLICK)
	{
        pthread_t sound_thread;
        pthread_create(&sound_thread, NULL, shoot_sound_func, "cub3d_gun_shot_sound.wav");
        pthread_detach(sound_thread);
		game->scene->player->inventory->bullets--;
		printf("(right click detected) shot fired\n");
		// shoot_sound_func();
		bullet_shoot_func(game, game->scene->minimap->player_rotation);
	}
	if (button == SCROLL_DOWN)
		player->inventory->active_item += 1;
	else if (button == SCROLL_UP)
		player->inventory->active_item -= 1;
	if (player->inventory->active_item < 0)
		player->inventory->active_item = player->inventory->size - 1;
	if (player->inventory->active_item >= player->inventory->size)
		player->inventory->active_item = 0;
	player->update_count += 1;
	return (0);
}

// int	player_mouse_scroll(int button, int x, int y, t_player *player)
// {
// 	(void)x;
//     (void)y;
// 	// t_player *player;

// 	// player = game->scene->player;
// 	if (button == LEFT_CLICK)
// 	{
// 		printf("KABOOM12\n");
// 		bullet_shoot_func(game, game->scene->minimap->player_rotation);
// 	}
// 	if (button == SCROLL_DOWN)
// 		player->inventory->active_item += 1;
// 	else if (button == SCROLL_UP)
// 		player->inventory->active_item -= 1;
// 	if (player->inventory->active_item < 0)
// 		player->inventory->active_item = player->inventory->size - 1;
// 	if (player->inventory->active_item >= player->inventory->size)
// 		player->inventory->active_item = 0;
// 	player->update_count += 1;
// 	return (0);
// }

int			player_mouse_move(int x, int y, t_player *player)
{
	static int last_x;
    int dx;

	(void)y;
	if (last_x == 0)
	{
		last_x = x;
		return (0);
	}
	dx = x - last_x;
	player->rotation += dx * PLAYER_ROTATION_SPEED;
    if (player->rotation >= 360.0)
        player->rotation -= 360.0;
    else if (player->rotation < 0.0)
        player->rotation += 360.0;
    last_x = x;
    return (0);
}