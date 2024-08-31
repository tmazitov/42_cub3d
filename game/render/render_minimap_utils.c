/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:32:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/31 20:16:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	minimap_draw_enemies(t_game *game)
{
	t_enemy			*enemy;
	t_enemy_storage	*storage;
	t_sprite_node	*enemy_icon;
	int				counter;
	t_point			pos;

	storage = game->scene->enemies;
	enemy_icon = get_sprite_by_name(game->scene->map->sprites, "ENEMY_ICON");
	if (!enemy_icon || !enemy_icon->image)
		return ;
	counter = 0;
	while (counter < storage->size)
	{
		enemy = storage->enemies[counter];
		pos.x = enemy->pos->x;
		pos.y = enemy->pos->y;
		if (enemy->alive)
			minimap_draw_image(game->scene->minimap, enemy_icon->image, pos, 0);
		counter++;
	}
}

void	draw_minimap(t_game *game, t_image *image)
{
	t_point	p;

	p.x = MINIMAP_POS_X;
	p.y = MINIMAP_POS_Y;
	img_put_img(game->scene->image, image, p, 0);
}
