/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:22:01 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 13:59:54 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

static int	*make_pressed_buttons(int count)
{	
	int	*result;
	int	counter;

	result = malloc(sizeof(int) * count);
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

static t_inventory	*init_inventory()
{
	return (make_inventory(PLAYER_INV_CELL_AMOUNT));
}

static void init_player(t_player *player, t_direction direction)
{
	player->icon = NULL;
	player->pressed_buttons = NULL;
	player->move_vector = NULL;
	player->move_speed = 0;
	player->inventory = NULL;
	if (direction == NORTH)
		player->rotation = 90;
	else if (direction == SOUTH)
		player->rotation = -90;
	else if (direction == WEST)
		player->rotation = 180;
	else if (direction == EAST)
		player->rotation = 0;
}

t_player *make_player(void *mlx, t_point start_pos, t_direction direction)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	init_player(player, direction);	
	player->pos = make_point(start_pos.x+32, start_pos.y+32);
	if (!player->pos)
		return (free_player(player));
	player->move_vector = make_vector(0, 0);
	if (!player->move_vector)
		return (free_player(player));
	player->pressed_buttons = make_pressed_buttons(7);
	if (!player->pressed_buttons)
		return (free_player(player));
	player->icon = load_icon(mlx);
	if (!player->icon)
		return (free_player(player));
	player->inventory = init_inventory();
	if (!player->inventory)
		return (free_player(player));
	player->inventory->bullets = PLAYER_DEFAULT_BULLETS_COUNT;
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
	if (player->move_vector)
		free_vector(player->move_vector);
	free(player);
	return (NULL);
}