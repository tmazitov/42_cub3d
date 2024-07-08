/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:15:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/08 16:56:26 by tmazitov         ###   ########.fr       */
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

t_vector	*player_move_vector(t_player *player)
{
	float		modificator;
	t_vector	*move_vector;
	double		angle;
	float		x;
	float		y;
	int			counter;

	modificator = 1;
	move_vector = make_vector(0, 0);
	if (!move_vector)
		return (NULL);
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
			x = modificator * (PLAYER_SPEED) * cos(angle);
			y = modificator * (PLAYER_SPEED) * sin(angle);	
			vector_add(move_vector, x, y);
		}
		counter++;
	}
	return (move_vector);
}

void		player_move_update(t_player *player, t_vector *move_vector)
{
	if (!move_vector)
		return ;
	player->pos->x += move_vector->x;
	player->pos->y += move_vector->y;
}
