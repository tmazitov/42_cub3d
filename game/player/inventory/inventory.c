/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:01:38 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 13:57:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventory.h"

void	init_inventory(t_inventory *inventory)
{
	inventory->bullets = 0;
	inventory->size = 0;
	inventory->slots = NULL;
}

t_inventory	*make_inventory(int size)
{
	t_inventory	*inventory;

	inventory = malloc(sizeof(t_inventory));
	if (!inventory)
		return (NULL);
	init_inventory(inventory);
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
	free(inventory);
	return (NULL);
}