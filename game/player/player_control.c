/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:20:57 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/08 17:24:58 by tmazitov         ###   ########.fr       */
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
	else if (keycode == LEFT_ARROW)
		player->pressed_buttons[4] = value;
	else if (keycode == RIGHT_ARROW)
		player->pressed_buttons[5] = value;
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
	if (keycode == LEFT_ARROW)
		return (player->pressed_buttons[4]);
	if (keycode == RIGHT_ARROW)
		return (player->pressed_buttons[5]);
	return (0);
}

int	player_control_set(int keycode, t_player *player)
{
	// printf("w: %d\n", W_BUTTON);
	// printf("pressed: %d\n", keycode);
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