/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:23:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/25 04:51:48 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render_player_inventory(t_game *game)
{
	t_inventory	*inv;

	inv = game->scene->player->inventory;
	if (!inv || !inv->image)
		return ;
	img_put_img(game->scene->image, inv->image, *inv->pos, 0);	
}

void	render_player_weapon(t_game *game)
{
	t_inventory		*inv;
	t_item			*active_item;
	t_sprite_node	*sprite;
	t_point			pos;

	inv = game->scene->player->inventory;
	if (!inv || !inv->image)
		return ;
	active_item = inv->slots->items[inv->active_item];
	if (active_item && active_item->type == PISTOL)
	{
		sprite = get_sprite_by_name(game->scene->map->sprites, "PISTOL_SHOT_1");
		if (sprite && sprite->image)
		{
			pos.y = game->height - sprite->image->height;
			pos.x = (game->width - sprite->image->width) / 2 + 300 ;
			img_put_img(game->scene->image, sprite->image, pos, 0);
		}
	}
}

void	render_player(t_game *game)
{
	// render_player_bullets(game);
	render_player_weapon(game);
	render_player_inventory(game);
}