/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:59:26 by tmazitov          #+#    #+#             */
/*   Updated: 2024/03/13 13:03:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

static int	add_neighbour(t_a_point *origin, t_a_store *store, int x, int y)
{
	t_a_point	*point;

	point = a_check_by_coords(store, x, y);
	if (point == NULL)
	{
		point = make_a_point(x, y, origin);
		if (lst_add_point(store->opened, point) != 0)
			return (1);
		pnt_calc_weight(point, store->dest);
	}
	return (0);
}

static int	make_neighbours(t_a_point *origin, t_a_store *store)
{
	int	dx;
	int	x;
	int	y;

	if (!origin || !store)
		return (1);
	dx = NEIGHBOUR_DISTANCE;
	x = origin->x;
	y = origin->y;
	if (add_neighbour(origin, store, x + dx, y) != 0)
		return (1);
	if (add_neighbour(origin, store, x - dx, y) != 0)
		return (1);
	if (add_neighbour(origin, store, x, y + dx) != 0)
		return (1);
	if (add_neighbour(origin, store, x, y - dx) != 0)
		return (1);
	return (0);
}

static t_path	*prepare_result(t_a_point *active, t_a_point *dest)
{
	t_point_list	*result;
	t_point_list	*reversed;
	t_a_point		*point;
	t_a_point		*new;

	if (!active || !is_equal_point(active, dest))
		return (NULL);
	result = make_point_list();
	if (!result)
		return (NULL);
	point = active;
	while (point)
	{
		new = make_a_point(point->x, point->y, NULL);
		if (lst_add_point(result, new) != 0)
			return (free_point_list(result));
		if (!point->origin)
			break ;
		point = point->origin;
	}
	reversed = lst_reverse(result);
	free_point_list(result);
	return (make_path(reversed));
}

static void	free_all(t_a_store *store)
{
	free_point_list(store->opened);
	free_point_list(store->closed);
	free_a_point(store->dest);
	free(store);
}

t_path	*calc_path(t_a_point *src, t_a_point *dest, t_point_list *g_objs)
{
	t_path		*path;
	t_a_store	*store;
	t_a_point	*active;

	src = make_a_point(src->x, src->y, NULL);
	if (!src)
		return (NULL);
	store = make_a_store(src, dest, g_objs);
	if (!store)
		return (free_a_point(src));
	active = lst_get_min_point(store->opened);
	while (1)
	{
		if (make_neighbours(active, store) != 0)
			return (free_a_store(store));
		lst_rem_point(store->opened, active);
		lst_add_point(store->closed, active);
		if (active->heuristic_approxim == 0
			|| lst_length(store->opened) == 0)
			break ;
		active = lst_get_min_point(store->opened);
	}
	path = prepare_result(active, dest);
	free_all(store);
	return (path);
}
