/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:18:19 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/05 17:33:01 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->window = NULL;
	game->scene = NULL;
}

t_game	*make_game(char *scene_path, int width, int height, char *title)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	init_game(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free_game(game));
	game->window = mlx_new_window(game->mlx, width, height, title);
	if (!game->window)
		return (free_game(game));
	game->scene = make_scene(game->mlx, scene_path);
	if (!game->scene)
		return (free_game(game));
	game->height = height;
	game->width = width;
	game->blocker = 0;
	return (game);
}


void	*free_game(t_game *game)
{
	if (!game)
		return (NULL);
	game->blocker = 1;
	if (game->scene)
		free_scene(game->scene);
	// if (game->player)
	// 	free_player(game->player);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		free(game->mlx);
	free(game);
	return (NULL);
}

