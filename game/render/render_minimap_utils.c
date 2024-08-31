/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:32:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/31 23:08:17 by tmazitov         ###   ########.fr       */
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

t_rectangle	calc_door_rect(int x, int y)
{
	t_rectangle	rect;

	rect.start.x = x * 64;
	rect.start.y = y * 64;
	rect.height = 64;
	rect.width = 64;
	return (rect);
}

void	minimap_draw_doors(t_game *game)
{
	t_map_raw_list	*raw;
	t_point			pos;

	pos.y = 0;
	raw = game->scene->map->raw;
	while (pos.y < game->scene->map->height)
	{
		pos.x = 0;
		while (pos.x < game->scene->map->width)
		{
			if (get_raw_value(game->scene->map, pos.x, pos.y) == 'D')
			{
				minimap_draw_rect(game->scene->minimap, 
					calc_door_rect(pos.x, pos.y), 0x00293331);
			}
			pos.x++;
		}
		raw = raw->next;
		pos.y++;
	}
}

void	draw_minimap(t_game *game, t_image *image)
{
	t_point	p;

	p.x = MINIMAP_POS_X;
	p.y = MINIMAP_POS_Y;
	img_put_img(game->scene->image, image, p, 0);
}
