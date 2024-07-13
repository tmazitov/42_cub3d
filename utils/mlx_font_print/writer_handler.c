/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:30:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 21:44:22 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_font_print.h"

int	mlx_print_char(t_writer *w, char ch, int x, int y)
{
	void		*mlx;
	void		*win;
	void		*image;
	t_symbol	*symbol;

	if (!w)
		return (0);
	mlx = w->mlx;
	win = w->win;
	symbol = w->symbols;
	while (symbol && symbol->symbol != ch)
		symbol = symbol->next;
	if (!symbol)
		return (0);
	image = symbol->image->content;
	mlx_put_image_to_window(mlx, win, image, x, y);
	return (symbol->image->width);
}

int	mlx_print(t_writer *w, char *str, int x, int y)
{
	int	counter;

	if (!w || !str)
		return (0);
	counter = 0;
	while (str[counter])
	{
		if (str[counter] == ' ')
			x += w->space;
		else
			x += mlx_print_char(w, str[counter], x, y);
		counter++;
	}
	return (x);
}
