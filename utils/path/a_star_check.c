/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_star_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:57:56 by tmazitov          #+#    #+#             */
/*   Updated: 2023/11/26 19:19:55 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

t_a_point	*a_check_by_coords(t_a_store *store, int x, int y)
{
	t_a_point	*result;

	result = lst_check_by_coord(store->game_objs, x, y);
	if (result)
		return (result);
	result = lst_check_by_coord(store->opened, x, y);
	if (result)
		return (result);
	result = lst_check_by_coord(store->closed, x, y);
	return (result);
}
