/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bullets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:38:49 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/15 01:30:01 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"



void	player_add_bullets(t_player *player, int amount)
{
	int			health_bar_width;
	int			old_amount;
	t_inventory	*inv;

	old_amount = player->inventory->bullets;
	player->inventory->bullets += amount;
	player->update_count += 1;
	if (max_delimeter(old_amount) != max_delimeter(player->inventory->bullets))
	{
		inv = player->inventory;
		health_bar_width = inv->image->width - (INV_PADDING + INV_BORDER_SIZE) * 2 - bullets_message_size(inv);
		if (!hb_new_image(inv->image->mlx, inv->health_bar, health_bar_width, 24))
			return ;
	}

	printf("\t player collect bullets %d\n", amount);
}