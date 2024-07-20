/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:23:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/20 16:08:44 by tmazitov         ###   ########.fr       */
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
			img_draw(game->window, sprite->image, pos.x, pos.y);
			printf("active item %p %d\n", active_item,  sprite->image->height);
		}
	}
}

void	render_player(t_game *game)
{
	// render_player_bullets(game);
	render_player_weapon(game);
	render_player_inventory(game);
}