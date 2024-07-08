/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:22:01 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 17:10:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static int	*make_pressed_buttons(int count)
{	
	int	*result;
	int	counter;

	result = malloc(sizeof(int) * 6);
	if (!result)
		return (NULL);
	counter = 0;
	while (counter < count)
	{
		result[counter] = 0;
		counter++;
	}
	return (result);
}

t_player *make_player(void *mlx, t_point start_pos, t_direction direction)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->icon = NULL;
	player->pressed_buttons = NULL;
	player->pos = make_point(start_pos.x, start_pos.y);
	if (!player->pos)
		return (free_player(player));
	if (direction == NORTH)
		player->rotation = 90;
	else if (direction == SOUTH)
		player->rotation = -90;
	else if (direction == WEST)
		player->rotation = 180;
	else if (direction == EAST)
		player->rotation = 0;
	player->pressed_buttons = make_pressed_buttons(6);
	if (!player->pressed_buttons)
		return (free_player(player));
	player->icon = load_icon(mlx);
	if (!player->icon)
		return (free_player(player));
	return (player);
}

void *free_player(t_player *player)
{
	if (!player)
		return (NULL);
	if (player->pressed_buttons)
		free(player->pressed_buttons);
	if (player->pos)
		free_point(player->pos);
	if (player->icon)
		free_image(player->icon);
	free(player);
	return (NULL);
}