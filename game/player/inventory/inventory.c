/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:01:38 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/13 21:22:16 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventory.h"

void	init_inventory(t_inventory *inventory)
{
	inventory->bullets = 0;
	inventory->size = 0;
	inventory->pos = NULL;
	inventory->slots = NULL;
}

t_inventory	*make_inventory(int x, int y, int size)
{
	t_inventory	*inventory;

	inventory = malloc(sizeof(t_inventory));
	if (!inventory)
		return (NULL);
	init_inventory(inventory);
	inventory->pos = make_point(x, y);
	if (!inventory->pos)
		return (free_inventory(inventory));
	inventory->size = size;
	inventory->slots = make_item_collection(size);
	if (!inventory->slots)
		return (free_inventory(inventory));
	inventory->active_item = NULL;
	return (inventory);
}

void	*free_inventory(t_inventory *inventory)
{
	if (!inventory)
		return (NULL);
	if (inventory->pos)
		free(inventory->pos);
	free(inventory);
	return (NULL);
}