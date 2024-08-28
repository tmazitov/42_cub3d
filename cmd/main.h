/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:38:16 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/28 20:27:20 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H

# define MAIN_H

# include <mlx.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include "../game/game.h"
# include "../game/render/render.h"
# include "../game/update/update.h"

typedef struct s_ambient_sound
{
	t_game	*game;
	char	*sound_path;
}			t_ambient_sound;

# define KEY_PRESS 2

# define KEY_RELEASE 3

# define MOUSE_MOVE 6

void	ambient_sound(t_game *game, char *sound_path);
void	*ambient_sound_func(void *arg);

#endif 