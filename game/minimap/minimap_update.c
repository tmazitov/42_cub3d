/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:56:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 15:09:19 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	minimap_update(t_minimap *minimap)
{
	if (!minimap)
		return ;
	// minimap->player->x = game->player->x;
	// minimap->player->y = game->player->y;
	// minimap->player->angle = game->player->angle;
	minimap_update_image(minimap);
}

