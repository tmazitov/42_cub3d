/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:18:19 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/20 16:02:58 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->window = NULL;
	game->writer = NULL;
	game->scene = NULL;
	game->blocker = 0;
}

static int	set_inv_position(t_game *game, t_player *player)
{
	t_rectangle rect;
	t_inventory	*inv;

	inv = player->inventory;
	if (inv->image)
		return (1);
	rect.width = INV_CELL_SIZE * inv->size + INV_CELL_PADDING * (inv->size - 1) \
				+ (INV_BORDER_SIZE + INV_PADDING) * 2;
	rect.height = INV_CELL_SIZE * 2 + INV_CELL_PADDING \
				+ (INV_BORDER_SIZE + INV_PADDING) * 2;
	rect.start.x = game->width / 2 - (rect.width) / 2;
	rect.start.y = game->height - rect.height - 24;
	if (!inv_set_sizes(game->mlx, inv, rect))
		return (0);
	return (1);
}

static int	set_images_scale(t_game *game)
{
	t_sprite_node	*sprite;

	sprite = get_sprite_by_name(game->scene->map->sprites, "INV_BULLET");
	if (!sprite || !sprite->image)
		return (1);
	if (!img_scale(&sprite->image, 2))
		return (0);
	sprite = get_sprite_by_name(game->scene->map->sprites, "PISTOL_ICON");
	if (!sprite || !sprite->image)
		return (1);
	if (!img_scale(&sprite->image, 2))
		return (0);
	sprite = get_sprite_by_name(game->scene->map->sprites, "PISTOL_SHOT_1");
	if (!sprite || !sprite->image)
		return (1);
	if (!img_scale(&sprite->image, 10))
		return (0);
	sprite = get_sprite_by_name(game->scene->map->sprites, "PISTOL_SHOT_2");
	if (!sprite || !sprite->image)
		return (1);
	if (!img_scale(&sprite->image, 10))
		return (0);
	sprite = get_sprite_by_name(game->scene->map->sprites, "PISTOL_SHOT_3");
	if (!sprite || !sprite->image)
		return (1);
	if (!img_scale(&sprite->image, 10))
		return (0);
	sprite = get_sprite_by_name(game->scene->map->sprites, "PISTOL_SHOT_4");
	if (!sprite || !sprite->image)
		return (1);
	if (!img_scale(&sprite->image, 10))
		return (0);
	return (1); 
}

t_game	*make_game(char *scene_path, int width, int height, char *title)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	init_game(game);
	game->height = height;
	game->width = width;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free_game(game));
	game->window = mlx_new_window(game->mlx, width, height, title);
	if (!game->window)
		return (free_game(game));
	game->scene = make_scene(game->mlx, scene_path);
	if (!game->scene)
		return (free_game(game));
	game->writer = make_writer(game->mlx, game->window, 6);
	if (!game->writer \
		|| !setup_writer(game->writer, game->scene->map->sprites, 'a', 'z') \
		|| !setup_writer(game->writer, game->scene->map->sprites, '0', '9') \
		|| !set_inv_position(game, game->scene->player) \
		|| !set_images_scale(game))
		return (free_game(game));
	return (game);
}



void	*free_game(t_game *game)
{
	if (!game)
		return (NULL);
	game->blocker = 1;
	if (game->scene)
		free_scene(game->scene);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		free(game->mlx);
	if (game->writer)
		free_writer(game->writer);
	free(game);
	return (NULL);
}

