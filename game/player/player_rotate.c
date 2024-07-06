/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:27:15 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 20:27:47 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	player_rotate(t_player *player)
{
	if (player->pressed_buttons[4]) // pressed Left Arrow
		player->rotation -= PLAYER_ROTATION_SPEED;
	if (player->pressed_buttons[5]) // pressed Right Arrow
		player->rotation += PLAYER_ROTATION_SPEED;
}