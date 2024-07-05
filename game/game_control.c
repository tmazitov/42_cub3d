/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:19:10 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 01:02:11 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	player_can_move(t_game *game)
{
	return (1);
}

static int	action_is_movement(int keycode)
{
	return (keycode == A_BUTTON || \
			keycode == S_BUTTON || \
			keycode == D_BUTTON || \
			keycode == W_BUTTON || \
			keycode == LEFT_ARROW || \
			keycode == RIGHT_ARROW);
}

int	player_control_hook(int keycode, t_game *game)
{
	if (action_is_movement(keycode) && player_can_move(game))
		player_move(game->scene->player, keycode);
	return (0);
}