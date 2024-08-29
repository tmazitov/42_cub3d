/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 06:38:45 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/29 14:00:24 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static char	*get_frame_name(char *template, int number)
{
	char	*frame_name;
	char	*index_str;

	index_str = ft_itoa(number);
	if (!index_str)
		return (NULL);
	frame_name = ft_strjoin(template, index_str);
	free(index_str);
	if (!frame_name)
		return (NULL);
	return (frame_name);
}

t_anime	*make_pistol_shot_anime(t_game *game)
{
	int				counter;
	t_anime			*anime;
	t_sprite_node	*sprite;
	char			*sprite_name;

	anime = make_anime();
	if (!anime)
		return (NULL);
	counter = 0;
	while (counter < 4)
	{
		sprite_name = get_frame_name("PISTOL_SHOT_", counter + 1);
		if (!sprite_name)
			return (free_anime(anime));
		sprite = get_sprite_by_name(game->scene->map->sprites, sprite_name);
		if (!sprite || !sprite->image \
			|| !img_scale(&sprite->image, 10) \
			|| !anime_add_frame(anime, sprite->image, 1))
			return (free_anime(anime));
		free(sprite_name);
		counter++;
	}
	printf("\n|\\/\\/\\| Pistol shot animation created!\n");
	return (anime);
}

static t_anime	*make_enemy_move_anime(t_game *game)
{
	int				counter;
	t_anime			*anime;
	t_sprite_node	*sprite;
	char			*sprite_name;

	anime = make_anime();
	if (!anime)
		return (NULL);
	counter = 0;
	while (counter < 8)
	{
		sprite_name = get_frame_name("ENEMY_MOVE_", counter);
		if (!sprite_name)
			return (free_anime(anime));
		sprite = get_sprite_by_name(game->scene->map->sprites, sprite_name);
		if (!sprite || !sprite->image \
			|| !img_scale(&sprite->image, 10) \
			|| !anime_add_frame(anime, sprite->image, ENEMY_FRAME_DURATION))
			return (free_anime(anime));
		free(sprite_name);
		counter++;
	}
	printf("\n|\\/\\/\\| Enemy move animation created!\n");
	return (anime);
}

static t_anime	*make_enemy_attack_anime(t_game *game)
{
	int				counter;
	t_anime			*anime;
	t_sprite_node	*sprite;
	char			*sprite_name;

	anime = make_anime();
	if (!anime)
		return (NULL);
	counter = 0;
	while (counter < 6)
	{
		sprite_name = get_frame_name("ENEMY_ATTACK_", counter);
		if (!sprite_name)
			return (free_anime(anime));
		sprite = get_sprite_by_name(game->scene->map->sprites, sprite_name);
		if (!sprite || !sprite->image \
			|| !img_scale(&sprite->image, 10) \
			|| !anime_add_frame(anime, sprite->image, 2))
			return (free_anime(anime));
		free(sprite_name);
		counter++;
	}
	printf("\n|\\/\\/\\| Enemy attack animation created!\n");
	return (anime);
}

int	feel_enemies_animations(t_game *game)
{
	t_enemy_storage	*storage;
	int				counter;
	t_anime			*move_anime;
	t_anime			*attack_anime;

	move_anime = make_enemy_move_anime(game);
	if (!move_anime)
		return (0);
	attack_anime = make_enemy_attack_anime(game);
	if (!attack_anime)
		return (0);
	storage = game->scene->enemies;
	counter = 0;
	while (storage->enemies[counter]
		&& game->scene->map->zombie_count)
	{
		storage->enemies[counter]->attack_anime = anime_copy(attack_anime);
		storage->enemies[counter]->move_anime = anime_copy(move_anime);
		if (!storage->enemies[counter]->move_anime \
			|| !storage->enemies[counter]->attack_anime)
			return (free_anime(move_anime), free_anime(attack_anime), 0);
		counter++;
	}
	free_anime(move_anime);
	return (free_anime(attack_anime), 1);
}
