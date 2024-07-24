/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:10:24 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/24 16:57:17 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

# include <stdlib.h>
# include "../../utils/geometry/geometry.h"
# include "../../utils/image/image.h"

# define ENEMY_HEALTH_BAR_IMG_WIDTH 64
# define ENEMY_HEALTH_BAR_IMG_HEIGHT 16
# define ENEMY_HEALTH_BAR_BORDER_SIZE 2
# define ENEMY_HEALTH_BAR_BORDER_COLOR 2
# define ENEMY_HEALTH_BAR_FILL_COLOR 2
# define ENEMY_HEALTH_BAR_EMPTY_COLOR 2

typedef	struct s_enemy_image_collection
{
	t_image	*icon;
}		t_enemy_image_collection;


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
	t_enemy_health_bar	*hb;
	t_enemy_images		*images;
}		t_enemy;

t_enemy				*make_enemy(void *mlx, t_point pos, int health);
void				*free_enemy(t_enemy *enemy);

t_enemy_health_bar	*make_enemy_hb(void *mlx, int health);
void				*free_enemy_hb(t_enemy_health_bar *hb);

t_enemy_images		*make_enemy_images(t_enemy *enemy, t_enemy_image_collection coll);
void				*free_enemy_images(t_enemy_images *images);


#endif