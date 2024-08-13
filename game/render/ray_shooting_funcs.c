/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shooting_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:13:43 by kshamsid          #+#    #+#             */
/*   Updated: 2024/08/13 18:19:29 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void set_iterations(float player_angle, float* y_iteration, float* x_iteration)
{
    // Convert angle to radians for trigonometric functions
    float angle_rad = player_angle * (M_PI / 180.0);

    // Calculate the iterations using cosine and sine functions
    *x_iteration = BULLET_HIT_CHECK_ITERATION * cos(angle_rad);
    *y_iteration = BULLET_HIT_CHECK_ITERATION * sin(angle_rad);
}

static int check_if_bullet_in_zombie_range(t_point zomb_pos, t_point bullet_pos)
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
	int i;

	i = 0;
	while (i < zombz->size)
	{
		if (zombz->enemies[i]->hb->current >= 0
		&& check_if_bullet_in_zombie_range(*zombz->enemies[i]->pos, bullet) == 1)
		{
			printf("ENEMY FIRST HEALTH = %d\n",zombz->enemies[i]->hb->current);
			printf("shot_DAMAGE = %d\n", SHOT_DAMAGE);
			zombz->enemies[i]->hb->current -= SHOT_DAMAGE;
			if (zombz->enemies[i]->hb->current <= 0)
			{
				zombz->enemies[i]->alive = 0;
				return (/*printf("returning from check, zombie index %d hit\n", i),*/ 1);
			}
		}
		i++;
	}
	return (0);
}

// ZOMBIE_HITBOX_WIDTH 
int	zombie_hit_interaction(t_game *game, t_point bullet_iter)
{
	t_enemy_storage *zombz;

	zombz = game->scene->enemies;
	if (check_if_bullet_in_zombie_hitbox(zombz, bullet_iter) == 1)
		return (1);
	return (0);
}

//NEW MODIFICATION
t_line	*bullet_shoot_func(t_game *game, float angle_in_degrees)
{
	float	y_iteration;	//y_iteration in while loop
	float	x_iteration;	//x_iteration in while loop
	int		iterations;	//Like a Counter for block iterations to find the wall.
	float	angle_in_pie;	//angle in radians.
	t_line	*ray;	//final struct to return.

	if (angle_in_degrees < 0)
		angle_in_degrees += 360;
	if (angle_in_degrees > 360)
		angle_in_degrees -= 360;
	angle_in_pie = angle_in_degrees * PI / 180.0;
	set_iterations(game->scene->minimap->player_rotation, &y_iteration, &x_iteration);
	ray = make_line_by_points(game->scene->minimap->player_pos, game->scene->minimap->player_pos);
	if (!ray)
		return (NULL);
	iterations = 0;
	while (
		get_array_map_value(*ray, game) != '1'
		&& ray->end.x > 0
		&& ray->end.y > 0
		&& zombie_hit_interaction(game, ray->end) != 1
		&& iterations < BULLET_MAX_ITERATIONS
		)
	{
		line_update(ray, \
			ray->start.x, ray->start.y, \
			ray->end.x - x_iteration, \
			ray->end.y - y_iteration);
		iterations++;
	}
	// if (zombie_hit_interaction(game, ray->end) == 1)

	return (ray);
}
	// if (angle_in_degrees > 0 && angle_in_degrees < 180)
	// {
	// 	line_update(ray, \
	// 		ray->start.x, ray->start.y, \
	// 		ray->start.x - (fmod(ray->start.y, 64.0) / tan(angle_in_pie)), \
	// 		(ray->start.y - fmod(ray->end.y, 64.0) - 0.001));
	// 	y_iteration = -64;
	// 	x_iteration = y_iteration / tan(angle_in_pie);
	// }
	// else if (angle_in_degrees > 180 && angle_in_degrees < 360)
	// {
	// 	line_update(ray, \
	// 		ray->start.x, ray->start.y, \
	// 		ray->start.x + ((64 - fmod(ray->start.y, 64.0)) / tan(angle_in_pie)), \
	// 		ray->start.y - fmod(ray->end.y, 64.0) + 64);
	// 	y_iteration = 64;
	// 	x_iteration = y_iteration / tan(angle_in_pie);
	// }



//WORKING MALLOCING VERSION
// t_line	*ray_line_getter_y(t_game *game, float angle_in_degrees)
// {
// 	float	y_iteration;	//y_iteration in while loop
// 	float	x_iteration;	//x_iteration in while loop
// 	int		iterations;	//Like a Counter for block iterations to find the wall.
// 	float	angle_in_pie;	//angle in radians.
// 	t_line	*ray;	//final struct to return.

// 	if (angle_in_degrees < 0)
// 		angle_in_degrees += 360;
// 	if (angle_in_degrees > 360)
// 		angle_in_degrees -= 360;
// 	angle_in_pie = angle_in_degrees * PI / 180.0;
// 	y_iteration = 0;
// 	x_iteration = 0;
// 	ray = make_line_by_points(game->scene->minimap->player_pos, game->scene->minimap->player_pos);
// 	if (!ray)
// 		return (NULL);
// 	// if ((angle_in_degrees > 270 && angle_in_degrees <= 360)
// 	// 	|| (angle_in_degrees >= 0 && angle_in_degrees < 90))
// 	if ((angle_in_degrees > 270 || angle_in_degrees < 90))
// 	{
// 		line_update(ray, \
// 			ray->start.x, ray->start.y, \
// 			ray->start.x - fmod(ray->end.x, 64.0) - 0.001, \
// 			ray->start.y - (fmod(ray->start.x, 64.0) * tan(angle_in_pie)));
// 		x_iteration = -64;
// 		y_iteration = x_iteration * tan(angle_in_pie);
// 	}
// 	else if (angle_in_degrees > 90 && angle_in_degrees < 270)
// 	{
// 		line_update(ray, \
// 			ray->start.x, ray->start.y, \
// 			ray->start.x - fmod(ray->end.x, 64.0) + 64, \
// 			ray->start.y + ((64 - fmod(ray->start.x, 64.0)) * tan(angle_in_pie)));
// 		x_iteration = 64;
// 		y_iteration = x_iteration * tan(angle_in_pie);
// 	}
// 	else if (angle_in_degrees == 90 || angle_in_degrees == 270)
// 		return (free_line(ray));
// 	iterations = 0;
// 	while (
// 		get_array_map_value(*ray, game) != '1' &&
// 		ray->end.x > 0
// 		&& ray->end.y > 0 && iterations < PLAYER_VIEW_DEPTH)
// 	{
// 		line_update(ray, \
// 			ray->start.x, ray->start.y, \
// 			ray->end.x + x_iteration, \
// 			ray->end.y + y_iteration);
// 		iterations++;
// 	}
// 	return (ray);
// }

// t_line	*ray_line_shortest_xy(t_game *game, float angle_in_degrees)
// {
// 	t_line	*intersect_horizontal;
// 	t_line	*intersect_vertical;

// 	intersect_horizontal = ray_line_getter_x(game, angle_in_degrees);
// 	intersect_vertical = ray_line_getter_y(game, angle_in_degrees);
// 	if (!intersect_horizontal && !intersect_vertical)
// 		return (NULL);
// 	if (!intersect_horizontal)
// 		return (intersect_vertical);
// 	if (!intersect_vertical)
// 		return (intersect_horizontal);
// 	if (intersect_horizontal->length 
// 		< intersect_vertical->length)
// 		return (free_line(intersect_vertical), intersect_horizontal);
// 	else
// 		return (free_line(intersect_horizontal), intersect_vertical);
// }

