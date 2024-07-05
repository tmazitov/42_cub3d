/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:45:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/05 20:06:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	minimap_draw_walls(t_game *game)
{
	t_wall_node	*wall_node;

	wall_node = game->scene->map->walls->start;
	while (wall_node)
	{
		minimap_draw_wall(game->scene->minimap, wall_node->wall);
		wall_node = wall_node->next;
	}
}

static void	minimap_draw_free_space(t_game *game)
{
	int				x;
	int				y;
	t_rectangle		rect;
	t_map_raw_list	*raw_item;

	y = 0;
	rect.height = 64;
	rect.width = 64;
	raw_item = game->scene->map->raw;
	while (raw_item && y < game->scene->map->height)
	{
		x = 0;
		while (raw_item->value[x])
		{
			rect.start.x = (x) * 64;
			rect.start.y = (y) * 64;
			if (raw_item->value[x] != '1' && raw_item->value[x] != ' ')
			{
				minimap_draw_rect(game->scene->minimap, rect, MINIMAP_FREE_SPACE_COLOR);
			}
			x++;
		}
		y++;
		raw_item = raw_item->next;
	}
}

static void minimap_draw_player(t_minimap *minimap)
{
	t_rectangle rect;

	rect.start.x = minimap->player_pos.x + (64-PLAYER_ICON_SIZE)/2;
	rect.start.y = minimap->player_pos.y + (64-PLAYER_ICON_SIZE)/2;
	rect.width = PLAYER_ICON_SIZE;
	rect.height = PLAYER_ICON_SIZE;
	// printf("player pos %f %f\n", minimap->player_pos.x, minimap->player_pos.y);

	minimap_draw_rect(minimap, rect, MINIMAP_PLAYER_COLOR);
}

void	render_minimap(t_game *game)
{
	void	*win;
	void	*img;
	t_point	player_position;
	float	player_rotation;

	player_position.x = game->scene->player->pos->x;
	player_position.y = game->scene->player->pos->y;
	player_rotation = game->scene->player->rotation;
	minimap_update(game->scene->minimap, player_rotation, player_position);
	minimap_draw_background(game->scene->minimap);
	minimap_draw_free_space(game);
	minimap_draw_walls(game);
	minimap_draw_player(game->scene->minimap);
	minimap_draw_border(game->scene->minimap);
	win = game->window;
	img = game->scene->minimap->image;
	img_draw(win, img, MINIMAP_POS_X, MINIMAP_POS_Y);
}