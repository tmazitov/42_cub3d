/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:30:59 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/11 23:16:06 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

void	update_minimap(t_game *game)
{
	t_point	player_position;
	double	player_rotation;
	t_vector	*player_move;

	player_position.x = game->scene->player->pos->x;
	player_position.y = game->scene->player->pos->y;
	player_rotation = game->scene->player->rotation;
	player_move = game->scene->player->move_vector;
	minimap_update(game->scene->minimap, player_rotation, player_position, player_move);
}