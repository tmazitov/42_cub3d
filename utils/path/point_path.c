/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:06:21 by tmazitov          #+#    #+#             */
/*   Updated: 2023/12/10 21:36:23 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

// TODO :
// 		1. rename this package
//		2. make the struct s_path for the final path form src to the dest
//		3. s_path will contain the step counter and length
//		4. make the func get_next_step that return next step of the entered path

t_path	*make_path(t_point_list *list)
{
	t_path	*path;

	if (!list)
		return (NULL);
	path = malloc(sizeof(t_path));
	if (!path)
		return (NULL);
	path->point_list = list;
	path->counter = 0;
	path->length = lst_length(list);
	return (path);
}

t_a_point	*get_next_point(t_path *path)
{
	t_point_node	*node;
	int				counter;

	if (path->counter == path->length)
		return (NULL);
	counter = 0;
	node = path->point_list->points;
	while (node && counter != path->counter)
	{
		node = node->next;
		counter++;
	}
	if (path->length > path->counter)
		path->counter += 1;
	return (node->point);
}

void	*free_path(t_path *path)
{
	if (!path)
		return (NULL);
	if (path->point_list)
		free_point_list(path->point_list);
	free(path);
	return (NULL);
}
