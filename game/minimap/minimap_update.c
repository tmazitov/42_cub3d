/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:56:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/04 15:39:22 by tmazitov         ###   ########.fr       */
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
	img_clear(minimap->image);
}

