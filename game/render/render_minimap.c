/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:45:28 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/15 18:47:58 by kshamsid         ###   ########.fr       */
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
	t_line	ray;
	win = game->window;
	img = game->scene->minimap->image;
	minimap_draw_background(game->scene->minimap);
	minimap_draw_free_space(game);
	minimap_draw_walls(game);
	minimap_draw_player(game->scene->minimap, game->scene->player->icon);
	minimap_draw_border(game->scene->minimap);

	float temp_to_rotate = -30;
	while (temp_to_rotate < 60)
	{
		// printf("\t\t\t\t\t\t\t\t\t\tMinimap player ROT IN DEG %f\n", game->scene->minimap->player_rotation);
		// ray = ray_line_shortest_xy(game, game->scene->minimap->player_rotation + temp_to_rotate);
		ray = ray_line_getter_x(game, game->scene->minimap->player_rotation);
		ray.start.x /= 4;
		ray.start.y /= 4;
		ray.start.x += MINIMAP_BORDER_SIZE;
		ray.start.y += MINIMAP_BORDER_SIZE;
		ray.end.x /= 4;
		ray.end.y /= 4;
		ray.end.x += MINIMAP_BORDER_SIZE;
		ray.end.y += MINIMAP_BORDER_SIZE;
		
		// printf("\t\t\t\t\t\tMinimap ray start %f %f\n", ray.start.x, ray.start.y);
		// printf("\t\t\t\t\t\tMinimap ray end %f %f\n", ray.end.x, ray.end.y);
		img_put_line(game->scene->minimap->image, 0xee4335, ray.start, ray.end);
		temp_to_rotate += 0.25;
	}
	img_draw(win, img, MINIMAP_POS_X, MINIMAP_POS_Y);
}
