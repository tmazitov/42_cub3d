/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 06:38:45 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/28 07:47:14 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static t_anime	*make_enemy_move_anime(t_game *game)
{
	t_sprite_node	*sprite;
	int				counter;
	t_anime			*anime;
	char			*index_str;
	char			*sprite_name;

	anime = make_anime();
	if (!anime)
		return (NULL);
	counter = 0;
	while (counter < 8)
	{
		index_str = ft_itoa(counter);
		if (!index_str)
			return (free_anime(anime));
		sprite_name = ft_strjoin("ENEMY_MOVE_", index_str);
		free(index_str);
		if (!sprite_name)
			return (free_anime(anime));
		sprite = get_sprite_by_name(game->scene->map->sprites, sprite_name);
		free(sprite_name);
		if (sprite && sprite->image)
		{
			if (!img_scale(&sprite->image, 5))
				return (free_anime(anime));
			if (!anime_add_frame(anime, sprite->image, ENEMY_FRAME_DURATION))
				return (free_anime(anime));
		} 
		counter++;
	}
	printf("\t|\\/\\/\\| Enemy move animation created!\n");
	return (anime);
}

static int	feel_enemies_animations(t_game *game)
{
	t_enemy_storage	*storage;
	int				counter;
	t_anime			*move_anime;

	move_anime = make_enemy_move_anime(game);
	if (!move_anime)
		return (0);
	storage = game->scene->enemies; 
	counter = 0;
	while (storage->enemies[counter])
	{
		storage->enemies[counter]->move_anime = anime_copy(move_anime);
		if (!storage->enemies[counter]->move_anime)
			return (free_anime(move_anime), 0);
		counter++;
	}
	free_anime(move_anime);
	return (1);	
}

int	feel_game_animations(t_game *game)
{
	if (!feel_enemies_animations(game))
		return (0);
	return (1);
}