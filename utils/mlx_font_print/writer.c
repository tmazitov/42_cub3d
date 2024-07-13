/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:44:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 21:11:36 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_font_print.h"

t_writer	*make_writer(void *mlx, void *win, int space)
{
	t_writer	*writer;

	writer = malloc(sizeof(t_writer));
	if (!writer)
		return (NULL);
	writer->symbols = NULL;
	writer->mlx = mlx;
	writer->win = win;
	writer->space = space;
	return (writer);
}

int	writer_add_symbol(t_writer *writer, char ch, t_image *image)
{
	t_symbol	*last;

	if (!writer)
		return (0);
	last = writer->symbols;
	while (last)
	{
		if (!last->next)
			break ;
		last = last->next;
	}
	if (last)
	{	
		last->next = make_symbol(ch, image);
		if (!last->next)
			return (0);
		return (1);
	}
	writer->symbols = make_symbol(ch, image);
	if (!writer->symbols)
		return (0);
	return (1);
}

void	*free_writer(t_writer *writer)
{
	if (!writer)
		return (NULL);
	if (writer->symbols)
		free_symbol(writer->symbols);
	free(writer);
	return (NULL);
}
