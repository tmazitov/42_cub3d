/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:15:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 22:12:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

static int	player_can_move(t_game *game, t_vector *move_vector)
{
	return (1);
}

void	update_player(t_game *game)
{
	t_vector	*move_vector;
	
	player_rotate(game->scene->player);
	move_vector = player_move_vector(game->scene->player);
	if (player_can_move(game, move_vector))
		player_move_update(game->scene->player, move_vector);
	free_vector(move_vector);
}