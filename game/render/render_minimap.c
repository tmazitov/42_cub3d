/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:45:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 18:34:05 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	minimap_draw_free_space(t_game *game)
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
				minimap_draw_rect(game->scene->minimap,
					rect, MINIMAP_FREE_SPACE_COLOR);
			x++;
		}
		y++;
		raw_item = raw_item->next;
	}
}

void	minimap_draw_player(t_minimap *minimap, t_image *player_icon)
{
	t_point	pos;
	double	angle;

	pos.x = minimap->player_pos.x - (64) / 2;
	pos.y = minimap->player_pos.y - (64) / 2;
	angle = minimap->player_rotation;
	minimap_draw_image(minimap, player_icon, pos, angle - 90);
	img_put_pixel(minimap->image, 0xe7f218, \
		minimap->player_pos.x / MINIMAP_SCALE
		+ MINIMAP_BORDER_SIZE - minimap->camera->x, \
		minimap->player_pos.y / MINIMAP_SCALE
		+ MINIMAP_BORDER_SIZE - minimap->camera->y);
}

void	minimap_draw_treasure_boxes(t_minimap *minimap, \
	t_image *treasure_icon, \
	t_image *treasure_empty_icon, \
	t_treasure_storage *storage)
{
	int			counter;
	t_treasure	*treasure;

	counter = 0;
	while (storage->boxes[counter])
	{
		treasure = storage->boxes[counter];
		if (storage->items[counter])
			minimap_draw_image(minimap, treasure_icon, *treasure->pos, 0);
		else
			minimap_draw_image(minimap, treasure_empty_icon, *treasure->pos, 0);
		counter++;
	}
}

void	helper_render_mini(t_game *game,
	t_render_mini *r_m)
{
	minimap_draw_background(game->scene->minimap);
	minimap_draw_free_space(game);
	minimap_draw_walls(game);
	minimap_draw_player(game->scene->minimap, game->scene->player->icon);
	if (game->scene->map->zombie_count != 0)
	{
		minimap_draw_enemies(game);
	}
	r_m->treasure_sprite = get_sprite_by_name(game
			->scene->map->sprites, "TB_MINI");
	r_m->treasure_sprite_empty = get_sprite_by_name(game
			->scene->map->sprites, "TB_MINI_EMPTY");
}
		// render_enemy_path(game);

void	render_minimap(t_game *game)
{
	t_render_mini	*r_m;
	t_point			p;

	r_m = malloc(sizeof(t_render_mini));
	if (!r_m)
		return ;
	r_m->img = game->scene->minimap->image;
	helper_render_mini(game, r_m);
	if (r_m->treasure_sprite && r_m->treasure_sprite->image
		&& r_m->treasure_sprite_empty && r_m->treasure_sprite_empty->image)
	{
		minimap_draw_treasure_boxes(game->scene->minimap, \
			r_m->treasure_sprite->image,
			r_m->treasure_sprite_empty->image,
			game->scene->treasures);
	}
	minimap_draw_border(game->scene->minimap);
	p.x = MINIMAP_POS_X;
	p.y = MINIMAP_POS_Y;
	img_put_img(game->scene->image, r_m->img, p, 0);
	free(r_m);
}
