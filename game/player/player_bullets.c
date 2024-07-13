/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bullets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:38:49 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/13 21:22:48 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	player_add_bullets(t_player *player, int amount)
{
	player->inventory->bullets += amount;
	printf("\t player collect bullets %d\n", amount);
}