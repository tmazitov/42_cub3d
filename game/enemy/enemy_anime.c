/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_anime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:47:32 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/28 06:37:38 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

int	make_enemy_anime(t_enemy *enemy)
{
	if (!enemy)
		return (0);
	enemy->move_anime = make_anime();
	if (!enemy->move_anime)
		return (0);
	return (1);
}

void	*free_enemy_anime(t_enemy *enemy)
{
	if (enemy->move_anime) 
		free_anime(enemy->move_anime);
	return (NULL);
}