/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:15:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 21:31:06 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static int	is_diagonal_move(t_player *player)
{
	int	*pr;
	int	diagonal_cases[4];
	int	result;

	pr = player->pressed_buttons;
	diagonal_cases[0] = pr[0] && pr[1] && !pr[3];
	diagonal_cases[1] = pr[0] && pr[3] && !pr[1];
	diagonal_cases[2] = pr[2] && pr[1] && !pr[3];
	diagonal_cases[3] = pr[2] && pr[3] && !pr[1];
	result = diagonal_cases[0] || diagonal_cases[1] || diagonal_cases[2]
		|| diagonal_cases[3];
	return (result);
}

int	is_player_move(t_player *player)
{
	return (player->pressed_buttons[0] || player->pressed_buttons[1]
		|| player->pressed_buttons[2] || player->pressed_buttons[3]);
}

static void	update_move_vector(float modification, float speed, t_player *pl,
		t_vector *move_vector)
{
	float	x;
	float	y;
	int		counter;
	double	angle;

	counter = 0;
	while (counter < 4)
	{
		angle = pl->rotation * PI / 180.0;
		if (pl->pressed_buttons[counter] && counter == 0)
			angle += 0;
		else if (pl->pressed_buttons[counter] && counter == 1)
			angle += PI / 2;
		else if (pl->pressed_buttons[counter] && counter == 2)
			angle += PI;
		else if (pl->pressed_buttons[counter] && counter == 3)
			angle += 3 * PI / 2;
		if (pl->pressed_buttons[counter])
		{
			x = modification * speed * cos(angle);
			y = modification * speed * sin(angle);
			vector_add(move_vector, x, y);
		}
		counter++;
	}
}

t_vector	*player_move_vector(t_player *player, t_scene *scene)
{
	float		modification;
	t_vector	*move_vector;
	float		speed;

	speed = player_speed(player);
	if ((speed == 0 && scene->prev_speed != 0))
		scene->moves_made++;
	scene->prev_speed = speed;
	modification = 1;
	move_vector = make_vector(0, 0);
	if (!move_vector || speed == 0)
		return (free_vector(move_vector), NULL);
	if (!is_player_move(player) && speed != 0)
	{
		move_vector->x = (player->move_vector->x / player->move_speed) * speed;
		move_vector->y = (player->move_vector->y / player->move_speed) * speed;
		player->move_speed = speed;
		return (move_vector);
	}
	if (is_diagonal_move(player))
		modification = sqrt(2) / 2;
	player->move_speed = speed;
	update_move_vector(modification, speed, player, move_vector);
	return (move_vector);
}

void	player_move_update(t_player *player, t_vector *move_vector)
{
	if (!move_vector)
		return ;
	player->pos->x += move_vector->x;
	player->pos->y += move_vector->y;
	player->move_vector->x = move_vector->x;
	player->move_vector->y = move_vector->y;
}
