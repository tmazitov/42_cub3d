/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:00:02 by tmazitov          #+#    #+#             */
/*   Updated: 2023/12/10 21:57:11 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

static t_point_list	*make_open_list(t_a_point *src)
{
	t_point_list	*result;

	result = make_point_list();
	if (!result)
		return (NULL);
	if (lst_add_point(result, src) != 0)
		return (NULL);
	return (result);
}

t_a_store	*make_a_store(t_a_point *src, t_a_point *dest, t_point_list *g_objs)
{
	t_a_store	*store;

	store = malloc(sizeof(t_a_store));
	if (!store)
		return (store);
	store->game_objs = NULL;
	store->opened = NULL;
	store->closed = NULL;
	store->dest = NULL;
	store->game_objs = g_objs;
	if (!store->game_objs)
		return (free_a_store(store));
	store->opened = make_open_list(src);
	if (!store->opened)
		return (free_a_store(store));
	store->closed = make_point_list();
	if (!store->closed)
		return (free_a_store(store));
	store->dest = make_a_point(dest->x, dest->y, NULL);
	if (!store->dest)
		return (free_a_store(store));
	return (store);
}

void	*free_a_store(t_a_store *store)
{
	if (store->opened)
		free_point_list(store->opened);
	if (store->closed)
		free_point_list(store->closed);
	if (store->dest)
		free_a_point(store->dest);
	free(store);
	return (NULL);
}
