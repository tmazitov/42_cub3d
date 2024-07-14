/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:23:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 16:06:22 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render_player_inventory(t_game *game)
{
	t_inventory		*inv;
	t_sprite_node	*sprite;
	int				counter;
	int 			inventory_x;
	int 			inventory_y;
	
	inventory_x = game->width / 2 - (PLAYER_INV_CELL_SIZE * PLAYER_INV_CELL_AMOUNT + PLAYER_INV_CELL_PADDING * (PLAYER_INV_CELL_AMOUNT - 1)) / 2;
	inventory_y = game->height - PLAYER_INV_CELL_SIZE - 24; 
	inv = game->scene->player->inventory;
	sprite = get_sprite_by_name(game->scene->map->sprites, "INV_SLOT");
	if (!sprite || !sprite->image)
		return ;
	counter = 0;
	while (counter < inv->size)
	{
		mlx_put_image_to_window(game->mlx, game->window, sprite->image->content, \
			inventory_x, inventory_y);
		inventory_x += PLAYER_INV_CELL_SIZE + PLAYER_INV_CELL_PADDING;
		counter++;
	}
}

void	render_player_bullets(t_game *game)
{
	char	*str_value;
	int		x;
	int		y;
	t_sprite_node	*bullet;

	x = 280;
	y = 20;
	if (!game->writer)
		return ;
	str_value = ft_itoa(game->scene->player->inventory->bullets);
	if (!str_value)
		return ;
	bullet = get_sprite_by_name(game->scene->map->sprites, "INV_BULLET");
	if (!bullet || !bullet->image)
		return (free(str_value));
	img_draw(game->window, bullet->image, x, y);
	x += bullet->image->height + 10;
	y = y + bullet->image->height / 2 + 5;
	mlx_print(game->writer, str_value, x, y);
	free(str_value);
}

void	render_player(t_game *game)
{
	render_player_bullets(game);
	render_player_inventory(game);
}