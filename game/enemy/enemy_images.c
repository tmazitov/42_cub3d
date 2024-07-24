/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_images.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:47:32 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/24 15:56:09 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

t_enemy_images	*make_enemy_images(t_enemy *enemy, t_enemy_image_collection coll)
{
	t_enemy_images	*images;

	if (!coll.icon)
		return (print_error("invalid enemy images"), NULL);
	images = malloc(sizeof(t_enemy_images));
	if (!images)
		return (NULL);
	images->icon = coll.icon;
	enemy->images = images;
	return (images);
}

void	*free_enemy_images(t_enemy_images *images)
{
	// scene map have a game image storage and free it in this case  
	if (!images)
		return (NULL);
	free(images);
	return (NULL);		
}