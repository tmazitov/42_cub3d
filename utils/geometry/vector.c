/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:34:48 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/19 17:17:57 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_vector	*make_vector(float x, float y)
{
	t_vector	*vector;

	vector = (t_vector *)malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

void	*free_vector(t_vector *vector)
{
	if (!vector)
		return (NULL);
	free(vector);
	return (NULL);
}

void	vector_add(t_vector *vector, float x, float y)
{
	if (!vector)
		return ;
	vector->x += x;
	vector->y += y;
}