/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control_mouse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 01:47:25 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 20:21:47 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	*shoot_sound_func(void *arg)
{
	char		*sound_path;
	ma_result	result;
	ma_engine	engine;

	sound_path = (char *)arg;
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS)
		return (NULL);
	result = ma_engine_play_sound(&engine, sound_path, NULL);
	if (result != MA_SUCCESS)
	{
		ma_engine_uninit(&engine);
		return (NULL);
	}
	usleep(1000000);
	ma_engine_uninit(&engine);
	return (NULL); 
}

void	left_click_shoot_func(t_game *game)
{
	pthread_t	sound_thread;
	t_inventory	*inv;
	t_item		*active_item;

	inv = game->scene->player->inventory;
	if (!inv)
		return ;
	active_item = inv->slots->items[inv->active_item];
	if (active_item && active_item->type == PISTOL)
	{
		pthread_create(&sound_thread, NULL, shoot_sound_func,
			"cub3d_gun_shot_sound.wav");
		pthread_detach(sound_thread);
		game->scene->player->inventory->bullets--;
		bullet_shoot_func(game, game->scene->minimap->player_rotation);
	}
}

static void	player_mouse_scroll_handler(int button, t_player *player)
{
	if (button == SCROLL_DOWN)
		player->inventory->active_item += 1;
	else if (button == SCROLL_UP)
		player->inventory->active_item -= 1;
	if (player->inventory->active_item < 0)
		player->inventory->active_item = player->inventory->size - 1;
	if (player->inventory->active_item >= player->inventory->size)
		player->inventory->active_item = 0;
	if (button == SCROLL_DOWN || button == SCROLL_UP)
		player->update_count += 1;
}

static void	player_mouse_click_handler(int button, t_player *player,
		t_game *game)
{
	t_item		*player_active_item;
	pthread_t	sound_thread;

	if (button != LEFT_CLICK)
		return ;
	player_active_item = inv_get_active_item(player->inventory);
	if (button == LEFT_CLICK)
	{
		if (player_active_item
			&& player_active_item->type == PISTOL
			&& player->inventory->bullets > 0)
		{
			pthread_create(&sound_thread, NULL, shoot_sound_func, 
				"cub3d_gun_shot_sound.wav");
			pthread_detach(sound_thread);
			player->inventory->bullets--;
			player->anime_activated = 1;
			bullet_shoot_func(game, player->rotation);
			player->update_count += 1;
		}
	}
}

int	player_mouse_control(int button, int x, int y, t_game *game)
{
	t_player	*player;

	(void)x;
	(void)y;
	player = game->scene->player;
	player_mouse_click_handler(button, player, game);
	player_mouse_scroll_handler(button, player);
	return (0);
}
