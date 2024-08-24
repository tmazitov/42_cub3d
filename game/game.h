/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:17:46 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 22:56:29 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../utils/mlx_font_print/mlx_font_print.h"
# include "scene/scene.h"
# include <mlx.h>
# include <stdlib.h>

typedef struct s_scene	t_scene;

typedef struct s_game
{
	void				*mlx;
	void				*window;
	int					height;
	int					width;
	t_scene				*scene;
	t_writer			*writer;
	int					blocker;
}						t_game;

// GAME

void					*free_game(t_game *game);
t_game					*make_game(char *scene_path, int width, int height,
							char *title);
int						setup_writer(t_writer *writer,
							t_sprite_storage *storage, char from, char to);
int						feel_game_animations(t_game *game);
t_anime					*make_pistol_shot_anime(t_game *game);

// HOOKS
int						feel_enemies_animations(t_game *game);

int						player_control_hook(int keycode, t_game *game);

#endif // GAME_H