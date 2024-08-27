/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shooting_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:13:43 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/27 20:05:22 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	set_iterations(float player_angle, float *y_iteration,
	float *x_iteration)
{
	float	angle_rad;

	angle_rad = player_angle * (M_PI / 180.0);
	*x_iteration = BULLET_HIT_CHECK_ITERATION * cos(angle_rad);
	*y_iteration = BULLET_HIT_CHECK_ITERATION * sin(angle_rad);
}

static int	check_if_bullet_in_zombie_range(t_point zomb_pos,
	t_point bullet_pos)
{
	if (fabsf((zomb_pos.x + 32) - bullet_pos.x) < ZOMBIE_HITBOX_WIDTH / 2
		&& fabsf((zomb_pos.y + 32) - bullet_pos.y) < ZOMBIE_HITBOX_WIDTH / 2)
	{
		return (1);
	}
	return (0);
}

int	check_if_bullet_in_zombie_hitbox(t_enemy_storage *zombz, t_point bullet)
{
	int		i;

	i = 0;
	while (i < zombz->size)
	{
		if (zombz->enemies[i]->hb->current >= 0
			&& check_if_bullet_in_zombie_range(*zombz->enemies[i]->pos,
				bullet) == 1)
		{
			printf("ENEMY FIRST HEALTH = %d\n", zombz->enemies[i]->hb->current);
			printf("shot_DAMAGE = %d\n", SHOT_DAMAGE);
			zombz->enemies[i]->hb->current -= SHOT_DAMAGE;
			if (zombz->enemies[i]->hb->current <= 0)
			{
				zombz->enemies[i]->alive = 0;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

// ZOMBIE_HITBOX_WIDTH 
int	zombie_hit_interaction(t_game *game, t_point bullet_iter)
{
	t_enemy_storage	*zombz;

	zombz = game->scene->enemies;
	if (check_if_bullet_in_zombie_hitbox(zombz, bullet_iter) == 1)
		return (1);
	return (0);
}

//NEW MODIFICATION
void	bullet_shoot_func(t_game *game, float angle_in_degrees)
{
	float	y_i;
	float	x_i;
	int		iterations;
	t_line	*ray;

	if (angle_in_degrees < 0)
		angle_in_degrees += 360;
	if (angle_in_degrees > 360)
		angle_in_degrees -= 360;
	set_iterations(game->scene->minimap->player_rotation, &y_i, &x_i);
	ray = make_line_by_points(game->scene->minimap->player_pos,
			game->scene->minimap->player_pos);
	if (!ray)
		return ;
	iterations = 0;
	while (get_array_map_value(*ray, game) != '1' && ray->end.x > 0
		&& ray->end.y > 0 && zombie_hit_interaction(game, ray->end) != 1
		&& iterations < BULLET_MAX_ITERATIONS)
	{
		line_update_end(ray,
			ray->end.x - x_i, ray->end.y - y_i);
		iterations++;
	}
	free_line(ray);
}
