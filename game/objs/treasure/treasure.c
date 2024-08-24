/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treasure.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:29:25 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 17:26:07 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "treasure.h"

t_treasure	*make_treasure(float x, float y)
{
	t_treasure	*treasure;

	treasure = (t_treasure *)malloc(sizeof(t_treasure));
	if (!treasure)
		return (NULL);
	treasure->pos = NULL;
	treasure->center = NULL;
	treasure->pos = make_point(x, y);
	if (!treasure->pos)
		return (free_treasure(treasure));
	treasure->center = make_point(x + 32, y + 32);
	if (!treasure->center)
		return (free_treasure(treasure));
	return (treasure);
}

void	*free_treasure(t_treasure *treasure)
{
	if (!treasure)
		return (NULL);
	if (treasure->pos)
		free_point(treasure->pos);
	if (treasure->center)
		free_point(treasure->center);
	free(treasure);
	return (NULL);
}
