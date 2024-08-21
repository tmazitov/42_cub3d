/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:10:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/21 17:19:56 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

# include <stdlib.h>
# include "../../utils/geometry/geometry.h"
# include "../../utils/image/image.h"
# include "../../utils/path/path.h"

# define ENEMY_HEALTH_BAR_IMG_WIDTH 64
# define ENEMY_HEALTH_BAR_IMG_HEIGHT 16
# define ENEMY_HEALTH_BAR_BORDER_SIZE 2
# define ENEMY_HEALTH_BAR_BORDER_COLOR 2
# define ENEMY_HEALTH_BAR_FILL_COLOR 2
# define ENEMY_HEALTH_BAR_EMPTY_COLOR 2

# define ENEMY_ATTACK_COOLDOWN 12
# define ENEMY_ATTACK_DISTANCE 80

# define ENEMY_SPEED 4
# define ENEMY_FRAME_DURATION 4

# define SHOT_DAMAGE 1
typedef	struct s_enemy_health_bar
{
	int 	current;
	int 	max;
	t_image	*image;
}		t_enemy_health_bar;

typedef	struct s_enemy_images
{
	t_image	*icon;
}		t_enemy_images;


typedef struct s_enemy
{
	int					health;
	int					damage;
	int					alive;
	t_point				*pos;
	t_path				*path;
	t_enemy_health_bar	*hb;
	t_point				*move_target;
	t_anime				*move_anime;
	t_anime				*attack_anime;
	int					attack_cooldown;
	int					is_attack;
t_point				*player_pos;
}		t_enemy;

t_enemy				*make_enemy(void *mlx, t_point pos, int health);
void				*free_enemy(t_enemy *enemy);
int					make_enemy_anime(t_enemy *enemy);
void				*free_enemy_anime(t_enemy *enemy);

int					enemy_calc_move_target(t_enemy *enemy);
int					enemy_move(t_enemy *enemy, t_vector *vector);
t_vector			*enemy_calc_move_vector(t_enemy *enemy);
void				enemy_calc_path(t_enemy *enemy, t_point player_pos, t_point_list *objs_points);

t_enemy_health_bar	*make_enemy_hb(void *mlx, int health);
void				*free_enemy_hb(t_enemy_health_bar *hb);

int					enemy_attack_handler(t_enemy *enemy, t_point player_pos);
t_image				*enemy_get_image(t_enemy *enemy);
#endif