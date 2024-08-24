/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:23:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 21:41:45 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render_player_inventory(t_game *game)
{
	t_inventory	*inv;

	inv = game->scene->player->inventory;
	if (!inv || !inv->image)
		return ;
	img_put_img(game->scene->image, inv->image, *inv->pos, 0);	
}

t_image	*get_pistol_image(t_player *player)
{
	t_image		*image;

	image = anime_current_frame(player->pistol_anime);
	if (player->anime_activated >= player->pistol_anime->duration)
	{
		player->anime_activated = 0;
		player->pistol_anime->current_frame = player->pistol_anime->frames;
	} 
	else
		player->anime_activated++;
	return (image);
}

void	render_player_weapon(t_game *game)
{
	t_player		*player;
	t_item			*active_item;
	t_image			*image;
	t_point			pos;

	player = game->scene->player;
	if (!player->inventory || !player->inventory->image)
		return ;
	active_item = player->inventory->slots->items[player->inventory->active_item];
	if (active_item && active_item->type == PISTOL)
	{
		if (!game->scene->player->anime_activated)
			image = player->pistol_anime->frames->image;
		else
			image = get_pistol_image(player);
		pos.x = (game->width - image->width) / 2 + 300 ;
		pos.y = game->height - image->height;
		img_put_img(game->scene->image, image, pos, 0);
	}
}

// void	render_move_string(t_game *game)
// {
// 	char *string_put;

// 	string_put = ft_strjoin("Player Moves Made: ", ft_itoa(game->scene->moves_made));	
// 	mlx_string_put(game->mlx, game->window, 500, 500, 0x00FF0000, string_put);
// 	free(string_put);
// }

void	render_player(t_game *game)
{
	// render_player_bullets(game);
	render_player_weapon(game);
	render_player_inventory(game);
	// render_move_string(game);
}
