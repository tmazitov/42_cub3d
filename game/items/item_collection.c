/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_collection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:26:05 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 14:49:16 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"

t_item_collection	*make_item_collection(int size)
{
	t_item_collection	*collection;
	int					counter;

	collection = (t_item_collection *)malloc(sizeof(t_item_collection));
	if (!collection)
		return (NULL);
	collection->items = malloc(sizeof(t_item *) * (size + 1));
	if (!collection->items)
		return (free_item_collection(collection));
	counter = 0;
	while (counter < size + 1)
		collection->items[counter++] = NULL;
	collection->size = size;
	return (collection);
}

int	item_collection_add_item(t_item_collection *collection, t_item_type type, int amount)
{
	t_item	*item;
	int		counter;
	int		is_added;

	item = make_item(type, amount);
	if (!item)
		return (0);
	is_added = 0;
	counter = 0;
	while (counter < collection->size)
	{
		if (collection->items[counter] == NULL)
		{
			collection->items[counter] = item;
			is_added = 1;
		}
		counter++;
	}

	if (!is_added)
		return (free_item(item), 2);
	return (1);
}


	

void	*free_item_collection(t_item_collection *collection)
{
	int	counter;

	if (!collection)
		return (NULL);
	counter = 0;
	while (collection->items[counter])
		free_item(collection->items[counter++]);
	free(collection->items);
	free(collection);
	return (NULL);
}