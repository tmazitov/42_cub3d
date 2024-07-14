/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:23:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 18:10:43 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render_player_inventory(t_game *game)
{
	t_inventory	*inv;

	inv = game->scene->player->inventory;
	if (!inv || !inv->image)
		return ;
	img_draw(game->window, inv->image, inv->pos->x, inv->pos->y);
}

void	render_player(t_game *game)
{
	// render_player_bullets(game);
	render_player_inventory(game);
}