/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:45:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/11 22:07:12 by kshamsid         ###   ########.fr       */
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

static void minimap_draw_player(t_minimap *minimap, t_image *player_icon)
{
	t_point	pos;
	double	angle;

	pos.x = minimap->player_pos.x - (64)/2;
	pos.y = minimap->player_pos.y - (64)/2;
	angle = minimap->player_rotation;
	minimap_draw_image(minimap, player_icon, pos, angle - 90);
	img_put_pixel(minimap->image, 0xe7f218, minimap->player_pos.x / 4 + MINIMAP_BORDER_SIZE,  minimap->player_pos.y / 4 + MINIMAP_BORDER_SIZE);
}

void	render_minimap(t_game *game)
{
	void	*win;
	void	*img;

	win = game->window;
	img = game->scene->minimap->image;
	minimap_draw_background(game->scene->minimap);
	minimap_draw_free_space(game);
	minimap_draw_walls(game);
	minimap_draw_player(game->scene->minimap, game->scene->player->icon);
	minimap_draw_border(game->scene->minimap);

	t_point start;
	t_point str_finish;

	t_point end;

	start.x = 436;
	start.y = 426;
	str_finish.x = 100;
	str_finish.y = 100;

	end.x = game->scene->minimap->player_pos.x + 416;
	end.y = game->scene->minimap->player_pos.y + 416;

	printf("start pos %f %f\n", start.x, start.y);
	printf("str_finish pos %f %f\n", str_finish.x, str_finish.y);
	img_put_line(game->scene->minimap->image, 0xf00ed5, start, str_finish);

	printf("player pos %f %f\n", game->scene->minimap->player_pos.x, game->scene->minimap->player_pos.y);
	printf("end pos %f %f\n", end.x, end.y);
	img_put_line(game->scene->minimap->image, 0xf00ed5, game->scene->minimap->player_pos, end);
	printf("---------------\n");
	img_draw(win, img, MINIMAP_POS_X, MINIMAP_POS_Y);
}