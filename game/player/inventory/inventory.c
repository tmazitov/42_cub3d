/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:01:38 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 18:12:24 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventory.h"

void	init_inventory(t_inventory *inventory)
{
	inventory->bullets = 0;
	inventory->size = 0;
	inventory->slots = NULL;
	inventory->image = NULL;
	inventory->update_count = 1;
}

t_inventory	*make_inventory(int size)
{
	t_inventory	*inventory;

	inventory = malloc(sizeof(t_inventory));
	if (!inventory)
		return (NULL);
	init_inventory(inventory);
	inventory->pos = make_point(0, 0);
	if (!inventory->pos)
		return (free_inventory(inventory));
	inventory->size = size;
	inventory->slots = make_item_collection(size);
	if (!inventory->slots)
		return (free_inventory(inventory));
	inventory->active_item = NULL;
	return (inventory);
}

int	inv_set_sizes(void *mlx, t_inventory *inventory, t_rectangle rect)
{
	inventory->pos->x = rect.start.x;
	inventory->pos->y = rect.start.y;
	inventory->image = make_image(mlx);
	if (!inventory->image)
		return (0);
	if (!img_create(inventory->image, rect.width, rect.height))
		return (0);
	return (1);
}

void	*free_inventory(t_inventory *inventory)
{
	if (!inventory)
		return (NULL);
	if (inventory->slots)
		free_item_collection(inventory->slots);
	if (inventory->image)
		free_image(inventory->image);
	if (inventory->pos)
		free_point(inventory->pos);
	free(inventory);
	return (NULL);
}