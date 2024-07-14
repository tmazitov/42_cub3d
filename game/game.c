/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:18:19 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 14:35:40 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->window = NULL;
	game->writer = NULL;
	game->scene = NULL;
}

int	setup_writer(t_writer *writer, t_sprite_storage *storage, char from, char to)
{
	char	ch;
	char	ch_big;
	char	*ch_str;
	char	*name;
	t_image	*image;
	t_sprite_node	*node;

	if (!writer || !storage)
		return (0);
	ch = from;
	
	while (ch <= to)
	{
		if (ch >= 'a' && ch <= 'z')
			ch_big = ch - 32;
		else
			ch_big = ch;
		ch_str = ft_strdup(" ");
		if (!ch_str)
			return (0);
		ch_str[0] = ch_big;
		name = ft_strjoin("CH_", ch_str);
		free(ch_str);
		if (!name)
			return (0);
		node = get_sprite_by_name(storage, name);
		free(name); 
		if (!node || !node->image)
			return (0);
		if (!img_scale(&node->image, 3))
			return (0);
		image = node->image;
		if (!writer_add_symbol(writer, ch, image))
			return (0);
		ch++;
	}
	return (1);
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
	game->writer = make_writer(game->mlx, game->window, 10);
	if (!game->writer)
		return (free_game(game));
	if (!setup_writer(game->writer, game->scene->map->sprites, 'a', 'z'))
		return (free_game(game));
	if (!setup_writer(game->writer, game->scene->map->sprites, '0', '9'))
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
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		free(game->mlx);
	if (game->writer)
		free_writer(game->writer);
	free(game);
	return (NULL);
}

