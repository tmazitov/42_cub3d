/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:22:01 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/05 23:48:08 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

t_player *make_player(void *mlx, t_point start_pos, t_direction direction)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->icon = NULL;
	player->pos = make_point(start_pos.x, start_pos.y);
	if (!player->pos)
		return (free_player(player));
	if (direction == NORTH)
		player->rotation = PI / 2;
	else if (direction == SOUTH)
		player->rotation = 3 * PI /2;
	else if (direction == WEST)
		player->rotation = PI;
	else if (direction == EAST)
		player->rotation = 0;
	player->icon = load_icon(mlx);
	if (!player->icon)
		return (free_player(player));
	return (player);
}

void *free_player(t_player *player)
{
	if (!player)
		return (NULL);
	if (player->pos)
		free_point(player->pos);
	if (player->icon)
		free_image(player->icon);
	free(player);
	return (NULL);
}