/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control_mouse_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:22:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 20:22:27 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

int	player_mouse_move(int x, int y, t_player *player)
{
	static int	last_x;
	int			dx;

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
