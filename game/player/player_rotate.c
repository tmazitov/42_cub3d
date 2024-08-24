/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:27:15 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 20:17:49 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	player_rotate(t_player *player)
{
	int	rotate_vector;

	rotate_vector = 0;
	if (player->pressed_buttons[4])
	{
		if (player->rotation < 0)
			rotate_vector += 360;
		rotate_vector -= PLAYER_ROTATION_SPEED;
	}
	if (player->pressed_buttons[5])
	{
		if (player->rotation > 360)
			rotate_vector -= 360;
		rotate_vector += PLAYER_ROTATION_SPEED;
	}
	player->rotation += rotate_vector;
}
