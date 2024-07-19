/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:01:38 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/19 23:26:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventory.h"

void	init_inventory(t_inventory *inventory)
{
	inventory->bullets = 0;
	inventory->size = 0;
	inventory->slots = NULL;
	inventory->health_bar = NULL;
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
	inventory->health_bar = make_health_bar(100);
	if (!inventory->health_bar)
		return (free_inventory(inventory));
	inventory->active_item = inventory->slots->items[0];
	return (inventory);
}

int	bullets_message_size(t_inventory *inventory)
{
	int		bullets;
	int		count;
	int		delimeter;

	count = 1;
	delimeter = 1;
	bullets = inventory->bullets;
	while (bullets / delimeter >= 10)
	{
		count++;
		delimeter *= 10;
	}
	return (count * 48 + 50 + INV_CELL_PADDING);
}

int	inv_set_sizes(void *mlx, t_inventory *inventory, t_rectangle rect)
{
	int		health_bar_width;

	inventory->pos->x = rect.start.x;
	inventory->pos->y = rect.start.y;
	inventory->image = make_image(mlx);
	if (!inventory->image)
		return (0);
	if (!img_create(inventory->image, rect.width, rect.height))
		return (0);
	health_bar_width = inventory->image->width - (INV_PADDING + INV_BORDER_SIZE) * 2 - bullets_message_size(inventory);
	if (!hb_new_image(mlx, inventory->health_bar, health_bar_width, 24))
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
	if (inventory->health_bar)
		free_health_bar(inventory->health_bar);
	free(inventory);
	return (NULL);
}