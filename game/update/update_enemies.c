/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:17:44 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/21 16:19:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"

// 
static void	remove_end(t_path *path)
{
	t_point_node	*node;
	t_point_node	*prev;

	if (!path)
		return ;
	prev = NULL;
	node = path->point_list->points;
	while (node && node->next)
	{
		prev = node;
		node = node->next;	
	}
	if (node == path->point_list->points)
		path->point_list->points = free_point_node(node);
	else
		prev->next = free_point_node(node);
	path->length -= 1;
}
// 

static void update_enemy_path(t_enemy *enemy, t_game *game)
{
	t_point		player_rel_pos;
	t_player	*pl;

	pl = game->scene->player;
	player_rel_pos.x = (int)(pl->pos->x / 64) * 64;
	player_rel_pos.y = (int)(pl->pos->y / 64) * 64;
	if (!point_is_equal(player_rel_pos, *enemy->player_pos))
		enemy->path = free_path(enemy->path);
	// 
	if (!enemy->path && !enemy->move_target)
	{
		enemy_calc_path(enemy, player_rel_pos, game->scene->objs_points);
		if (enemy->path)
			remove_end(enemy->path);
	}
	// 
}

static void	update_enemy_pos(t_enemy *enemy)
{
	t_vector	*move_vector;

	if (!enemy_calc_move_target(enemy))
		return ;
	move_vector = enemy_calc_move_vector(enemy);
	if (!move_vector)
		return ;
	enemy_move(enemy, move_vector);
	free_vector(move_vector);
}

static void	update_enemy(t_enemy *enemy, t_game *game)
{
	int			is_player_attacked;
	t_player	*player;
	
	player = game->scene->player;
	if (enemy->hb->current <= 0 && enemy->alive)
	{
		enemy->alive = 0;
		game->scene->enemies->alive -= 1;
	}
	if (!enemy->alive)
		return ;
	is_player_attacked = enemy_attack_handler(enemy, *player->pos);
	if (is_player_attacked == 2) // enemy attack cooldown
		return ;
	else if (is_player_attacked == 0) // player is not near
	{
		enemy->is_attack = 0;
		update_enemy_path(enemy, game);
		update_enemy_pos(enemy);
	}
	else if (is_player_attacked == 1) // enemy attacked
	{
		enemy->is_attack = 1;
		hb_add_damage(player->inventory->health_bar, 15); 
		player->inventory->update_count += 1;
	}
}

void	update_enemies(t_game *game)
{
	t_enemy_storage	*storage;
	int				counter;
	t_enemy			*enemy;

	storage = game->scene->enemies;
	counter = 0;
	while (counter < storage->size)
	{
		enemy = storage->enemies[counter];
		if (enemy->alive) 
			update_enemy(enemy, game);		
		counter++;
	}
}