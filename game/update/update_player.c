/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:15:35 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/06 16:58:39 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

static int	player_can_move(t_game *game)
{
	return (1);
}

void	update_player(t_game *game)
{
	if (player_can_move(game))
		player_move(game->scene->player);
}