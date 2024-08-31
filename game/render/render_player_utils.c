/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:37:00 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/31 20:16:10 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	prepare_image(t_game *game, t_image *image, int count)
{
	t_point			pos;
	char			*zombie_count;
	t_sprite_node	*node;

	node = get_sprite_by_name(game->scene->map->sprites, "ENEMY_ICON");
	if (!node || !node->image)
		return ;
	pos.x = 0;
	pos.y = 0; 
	img_put_img(image, node->image, pos, 0);
	pos.x = node->image->width + 16;
	zombie_count = ft_itoa(count);
	if (!zombie_count)
		return ;
	mlx_print_to_image(game->writer, image, zombie_count, pos);
	free(zombie_count);
}

void	render_player_zombies(t_game *game)
{
	t_point			pos;
	static int		local_alive;
	t_image			*image;

	image = game->scene->enemy_counter;
	pos.x = MINIMAP_POS_X;
	pos.y = MINIMAP_POS_Y * 2 + MINIMAP_SIZE;
	if (local_alive == game->scene->enemies->alive)
	{
		img_put_img(game->scene->image, image, pos, 0);
		return ;
	}
	img_clear(image);
	local_alive = game->scene->enemies->alive;
	prepare_image(game, image, local_alive);
	img_put_img(game->scene->image, image, pos, 0);
}
