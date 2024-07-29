/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control_keyboard.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:20:57 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/29 21:21:43 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static void	player_control_update(t_player *player, int keycode, int value)
{
	if (keycode == W_BUTTON)
		player->pressed_buttons[0] = value;
	else if (keycode == A_BUTTON)
		player->pressed_buttons[1] = value;
	else if (keycode == S_BUTTON)
		player->pressed_buttons[2] = value;
	else if (keycode == D_BUTTON)
		player->pressed_buttons[3] = value;
	// else if (keycode == LEFT_ARROW)
	// 	player->pressed_buttons[4] = value;
	// else if (keycode == RIGHT_ARROW)
	// 	player->pressed_buttons[5] = value;
	else if (keycode == F_BUTTON)
		player->pressed_buttons[6] = value;\
	if (keycode == ESC_BUTTON)
	{
		exit(1);
		//create proper exiting and freeing.
		// return (player->pressed_buttons[/*7*/]);
	}
}

static int key_is_active(t_player *player, int keycode)
{
	if (keycode == W_BUTTON)
		return (player->pressed_buttons[0]);
	if (keycode == A_BUTTON)
		return (player->pressed_buttons[1]);
	if (keycode == S_BUTTON)
		return (player->pressed_buttons[2]);
	if (keycode == D_BUTTON)
		return (player->pressed_buttons[3]);
	// if (keycode == LEFT_ARROW)
	// 	return (player->pressed_buttons[4]);
	// if (keycode == RIGHT_ARROW)
	// 	return (player->pressed_buttons[5]);
	if (keycode == F_BUTTON)
		return (player->pressed_buttons[6]);
	return (0);
}

static int player_inv_active_item(t_player *player, int keycode)
{
	int	new_active;

	new_active = -1;
	if (keycode == N1_BUTTON)
		new_active = 0;
	else if (keycode == N2_BUTTON)
		new_active = 1;
	else if (keycode == N3_BUTTON)
		new_active = 2;
	else if (keycode == N4_BUTTON)
		new_active = 3;
	else if (keycode == N5_BUTTON)
		new_active = 4;
	else if (keycode == N6_BUTTON)
		new_active = 5;
	if (keycode >= N1_BUTTON && keycode <= N6_BUTTON && new_active != player->inventory->active_item)
	{
		player->update_count += 1;
		player->inventory->active_item = new_active;
	}	
	return (0);
}


int	player_control_set(int keycode, t_player *player)
{
	// printf("w: %d\n", W_BUTTON);
	// printf("pressed %d\n", keycode);
	player_inv_active_item(player, keycode);
	if (!key_is_active(player, keycode))
		player_control_update(player, keycode, 1);
	return (0);
}

int	player_control_unset(int keycode, t_player *player)
{
	// printf("unpressed: %d\n", keycode);
	if (key_is_active(player, keycode))
		player_control_update(player, keycode, 0);
	return (0);
}
