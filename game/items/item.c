/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:08:48 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 14:09:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"

t_item	*make_item(t_item_type type, int amount)
{
	t_item	*item;

	item = (t_item *)malloc(sizeof(t_item));
	if (!item)
		return (NULL);
	item->type = type;
	item->amount = amount;
	return (item);
}

void	*free_item(t_item *item)
{
	if (!item)
		return (NULL);
	free(item);
	return (NULL);
}