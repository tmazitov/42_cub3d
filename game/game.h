/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:17:46 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/20 20:35:39 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdlib.h>
# include <mlx.h>
# include "scene/scene.h"
# include "../utils/mlx_font_print/mlx_font_print.h"

struct s_scene;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			height;
	int			width;
	t_scene		*scene;
	t_writer	*writer;
	int			blocker;
}				t_game;

// GAME

void			*free_game(t_game *game);
t_game			*make_game(char *scene_path, int width, int height, char *title);
int				setup_writer(t_writer *writer, t_sprite_storage *storage, char from, char to);


// HOOKS

int				player_control_hook(int keycode, t_game *game);
#endif // GAME_H