/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:32:11 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/27 18:41:36 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	minimap_draw_walls(t_game *game)
{
	t_wall_node	*wall_node;

	wall_node = game->scene->map->walls->start;
	while (wall_node)
	{
		minimap_draw_wall(game->scene->minimap, wall_node->wall);
		wall_node = wall_node->next;
	}
}

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
