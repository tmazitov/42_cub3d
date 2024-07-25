/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:34:30 by tmazitov          #+#    #+#             */
/*   Updated: 2023/12/10 21:36:20 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

t_point_node	*make_point_node(t_a_point *point)
{
	t_point_node	*node;

	if (!point)
		return (NULL);
	node = malloc(sizeof(t_point_node));
	if (!node)
		return (NULL);
	node->point = point;
	node->next = NULL;
	return (node);
}

void	*free_point_node(t_point_node *node)
{
	if (!node)
		return (NULL);
	if (node->point)
		free_a_point(node->point);
	free(node);
	return (NULL);
}
