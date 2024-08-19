/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_attack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:04:04 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/19 15:52:50 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

/// @brief Implement enemy attack with cooldown.
/// @param enemy - enemy instance that will attack
/// @param player_pos - current player position
/// @return If current enemy is attacked the function will return 1
/// @return If current enemy is attacked and in cooldown will return 2
/// @return If current enemy can not to attack
int	enemy_attack_handler(t_enemy *enemy, t_point player_pos)
{
	int	is_player_near;
	
	if (!enemy)
		return (0);
	is_player_near = distance(player_pos.x, player_pos.y, enemy->pos->x, enemy->pos->y) <= ENEMY_ATTACK_DISTANCE;
	if (!is_player_near && enemy->attack_cooldown)
		enemy->attack_cooldown = 0;
	if (!is_player_near)
		return (0);
	else if (enemy->attack_cooldown && enemy->attack_cooldown < ENEMY_ATTACK_COOLDOWN) 
	{
		enemy->attack_cooldown += 1;
		return (2);
	}
	else if (enemy->attack_cooldown == ENEMY_ATTACK_COOLDOWN)
		enemy->attack_cooldown = 0;
	if (enemy->attack_cooldown == 0)
	{
		enemy->attack_cooldown += 1;
		return (1);
	}
	return (0);
}