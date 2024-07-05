/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_behavior.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:15:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/05 20:07:00 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <stdio.h>

int	player_move(t_player *player, int keycode)
{
	if (keycode == W_BUTTON)
		player->pos->y += PLAYER_SPEED;
	else if (keycode == S_BUTTON)
		player->pos->y -= PLAYER_SPEED;
	else if (keycode == A_BUTTON)
		player->pos->x -= PLAYER_SPEED;
	else if (keycode == D_BUTTON)
		player->pos->x += PLAYER_SPEED;
	return (0);
}