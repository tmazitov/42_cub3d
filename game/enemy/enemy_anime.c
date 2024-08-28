/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_anime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:47:32 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/28 20:45:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

void	*free_enemy_anime(t_enemy *enemy)
{
	if (enemy->move_anime)
		free_anime(enemy->move_anime);
	if (enemy->attack_anime)
		free_anime(enemy->attack_anime);
	return (NULL);
}

t_image	*enemy_get_image(t_enemy *enemy)
{
	t_anime	*anime;

	if (!enemy->alive)
		return (NULL);
	if (enemy->is_attack)
		anime = enemy->attack_anime;
	else
		anime = enemy->move_anime;
	return (anime_current_frame(anime));
}
