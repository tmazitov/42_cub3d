/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_attack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:04:04 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/27 19:45:10 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniaudio/miniaudio.h"
#include "enemy.h"

static void	*shoot_sound_func(void *arg)
{
	char		*sound_path;
	ma_result	result;
	ma_engine	engine;

	sound_path = (char *)arg;
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS)
		return (NULL);
	result = ma_engine_play_sound(&engine, sound_path, NULL);
	if (result != MA_SUCCESS)
	{
		ma_engine_uninit(&engine);
		return (NULL);
	}
	usleep(1000000);
	ma_engine_uninit(&engine);
	return (NULL);
}

/// @brief Implement enemy attack with cooldown.
/// @param enemy - enemy instance that will attack
/// @param player_pos - current player position
/// @return If current enemy is attacked the function will return 1
/// @return If current enemy is attacked and in cooldown will return 2
/// @return If current enemy can not to attack
int	enemy_attack_handler(t_enemy *enemy, t_point player_pos)
{
	int			is_player_near;
	pthread_t	sound_thread;

	is_player_near = distance(player_pos.x, player_pos.y, enemy->pos->x + 32,
			enemy->pos->y + 32) <= ENEMY_ATTACK_DISTANCE;
	if (!is_player_near && !enemy->attack_cooldown)
		return (0);
	if (enemy->attack_cooldown < ENEMY_ATTACK_COOLDOWN)
		enemy->attack_cooldown += 1;
	else if (enemy->attack_cooldown == ENEMY_ATTACK_COOLDOWN)
		enemy->attack_cooldown = 0;
	if (enemy->attack_cooldown
		&& enemy->attack_cooldown < ENEMY_ATTACK_COOLDOWN)
		return (2);
	else if (enemy->attack_cooldown == 0 && is_player_near)
	{
		pthread_create(&sound_thread, NULL, shoot_sound_func,
			"punch-140236.mp3");
		pthread_detach(sound_thread);
		enemy->attack_cooldown = 1;
		return (1);
	}
	return (0);
}
