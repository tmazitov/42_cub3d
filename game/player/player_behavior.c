/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_behavior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:15:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 01:39:47 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <stdio.h>

int	player_move(t_player *player, int keycode)
{
	double rad = player->rotation * PI / 180.0;

	printf("keycode: %d\n", keycode);
	if (keycode == S_BUTTON)
	{
		player->pos->x += (PLAYER_SPEED) * cos(rad);
		player->pos->y += (PLAYER_SPEED) * sin(rad);
	}
	else if (keycode == W_BUTTON)
	{
		player->pos->x -= (PLAYER_SPEED) * cos(rad);
		player->pos->y -= (PLAYER_SPEED) * sin(rad);
	}
	else if (keycode == A_BUTTON)
	{
		player->pos->x += (PLAYER_SPEED) * cos(rad+PI/2);
		player->pos->y += (PLAYER_SPEED) * sin(rad+PI/2);
	}
	else if (keycode == D_BUTTON)
	{
		player->pos->x -= (PLAYER_SPEED) * cos(rad+PI/2);
		player->pos->y -= (PLAYER_SPEED) * sin(rad+PI/2);
	}
	else if (keycode == LEFT_ARROW)
		player->rotation -= PLAYER_ROTATION_SPEED;
	else if (keycode == RIGHT_ARROW)
		player->rotation += PLAYER_ROTATION_SPEED;
	return (0);
}