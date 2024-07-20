/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:15:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/20 20:34:38 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <stdio.h>

// static void	print_state(t_player *player)
// {
// 	int counter; 
	
// 	counter = 0;
// 	while (counter < 6)
// 	{
// 		printf("%d ", player->pressed_buttons[counter]);
// 		counter++;
// 	}
// 	printf("\n");
// }

static int	is_diagonal_move(t_player *player)
{
	return (player->pressed_buttons[0] \
			&& player->pressed_buttons[1] && !player->pressed_buttons[3]) || \
			(player->pressed_buttons[0] \
			&& player->pressed_buttons[3] && !player->pressed_buttons[1]) || \
			(player->pressed_buttons[2] \
			&& player->pressed_buttons[1] && !player->pressed_buttons[3]) || \
			(player->pressed_buttons[2] \
			&& player->pressed_buttons[3] && !player->pressed_buttons[1]);
}

int	is_player_move(t_player *player)
{
	return (player->pressed_buttons[0] || player->pressed_buttons[1] || \
			player->pressed_buttons[2] || player->pressed_buttons[3]);
}

t_vector	*player_move_vector(t_player *player)
{
	float		modificator;
	t_vector	*move_vector;
	double		angle;
	float		x;
	float		y;
	int			counter;
	float		speed;


	// print_state(player);

	speed = player_speed(player);
	if (speed == 0)
		return (NULL);
	modificator = 1;

	move_vector = make_vector(0, 0);
	if (!move_vector)
		return (NULL);
	if (!is_player_move(player) && speed != 0)
	{
		move_vector->x = (player->move_vector->x / player->move_speed) * speed;
		move_vector->y = (player->move_vector->y / player->move_speed) * speed;
		player->move_speed = speed;
		return (move_vector);
	}
	if (is_diagonal_move(player))
		modificator = sqrt(2) / 2;
	counter = 0;
	while (counter < 4)
	{	
		angle = player->rotation * PI / 180.0;
		if (player->pressed_buttons[counter] && counter == 0)
			angle += 0;
		else if (player->pressed_buttons[counter] && counter == 1)
			angle += PI/2;
		else if (player->pressed_buttons[counter] && counter == 2)
			angle += PI;
		else if (player->pressed_buttons[counter] && counter == 3)
			angle += 3*PI/2;
		if (player->pressed_buttons[counter])
		{
			x = modificator * (speed) * cos(angle);
			y = modificator * (speed) * sin(angle);	
			vector_add(move_vector, x, y);
		}
		counter++;
	}
	player->move_speed = speed;
	return (move_vector);
}

void		player_move_update(t_player *player, t_vector *move_vector)
{
	if (!move_vector)
		return ;
	player->pos->x += move_vector->x;
	player->pos->y += move_vector->y;
	player->move_vector->x = move_vector->x;
	player->move_vector->y = move_vector->y;
}
