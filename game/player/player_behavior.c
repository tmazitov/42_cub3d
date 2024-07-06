/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_behavior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:15:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 17:15:55 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <stdio.h>

static void	print_state(t_player *player)
{
	int counter; 
	
	counter = 0;
	while (counter < 6)
	{
		printf("%d ", player->pressed_buttons[counter]);
		counter++;
	}
	printf("\n");
}

int	player_move(t_player *player)
{
	double rad = player->rotation * PI / 180.0;

	print_state(player);

	if (player->pressed_buttons[0]) // pressed W
	{
		player->pos->x += (PLAYER_SPEED) * cos(rad);
		player->pos->y += (PLAYER_SPEED) * sin(rad);
	}
	if (player->pressed_buttons[1]) // pressed A
	{
		player->pos->x += (PLAYER_SPEED) * cos(rad+PI/2);
		player->pos->y += (PLAYER_SPEED) * sin(rad+PI/2);
	}
	if (player->pressed_buttons[2]) // pressed S
	{
		player->pos->x -= (PLAYER_SPEED) * cos(rad);
		player->pos->y -= (PLAYER_SPEED) * sin(rad);
	}
	if (player->pressed_buttons[3]) // pressed D
	{
		player->pos->x -= (PLAYER_SPEED) * cos(rad+PI/2);
		player->pos->y -= (PLAYER_SPEED) * sin(rad+PI/2);
	}
	if (player->pressed_buttons[4]) // pressed Left Arrow
	{
		player->rotation -= PLAYER_ROTATION_SPEED;
	}
	if (player->pressed_buttons[5]) // pressed Right Arrow
	{
		player->rotation += PLAYER_ROTATION_SPEED;
	}
	return (0);
}