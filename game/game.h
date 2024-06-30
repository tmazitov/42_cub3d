/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:17:46 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 14:55:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdlib.h>
# include <mlx.h>
# include "scene/scene.h"

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			height;
	int			width;
	t_scene		*scene;
	int			blocker;
}				t_game;

// GAME

void			*free_game(t_game *game);
t_game			*make_game(int width, int height, char *title);
// int				feed_game_writer(t_writer *writer);

// void			player_exit_handler(t_game *game);
// int				player_control_hook(int keycode, t_game *game);
#endif // GAME_H