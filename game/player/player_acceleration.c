/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_acceleration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 01:44:30 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/09 19:15:26 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static float	speed_increase(int x)
{
	return (pow(x, 2)/(9 * PLAYER_ACCELERATION_ITERS));
}

static float	speed_decrease(int x)
{
	return (-4 * pow(x, 2)/(9 * PLAYER_ACCELERATION_ITERS * 5) + 4);
}

float	player_speed(t_player *player)
{
	static int counter;
	static float speed;
	
	if (!is_player_move(player) && counter == 0 && speed == 0)
		return (0);
	else if (is_player_move(player) && speed >= PLAYER_MAX_SPEED)
	{
		speed = PLAYER_MAX_SPEED;
		return (speed);
	}
	else if (is_player_move(player))
	{
		speed = speed_increase(counter);
	}
	else if (speed > 0)
	{
		if (speed >= PLAYER_MAX_SPEED)
			counter = 0;
		speed = speed_decrease(counter) - 0.1;
	}	
	else if (counter != 0 && speed <= 0)
	{
		counter = 0;
		speed = 0;	
		return (speed);
	}
	counter += 1;
	return (speed);
}