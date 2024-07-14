/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:30:14 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 18:01:35 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_font_print.h"

int	mlx_print_char(t_writer *w, void *win, char ch, t_point pos)
{
	void		*mlx;
	void		*image;
	t_symbol	*symbol;

	if (!w)
		return (0);
	mlx = w->mlx;
	symbol = w->symbols;
	while (symbol && symbol->symbol != ch)
		symbol = symbol->next;
	if (!symbol)
		return (0);
	image = symbol->image->content;
	mlx_put_image_to_window(mlx, win, image, pos.x, pos.y);
	return (symbol->image->width);
}

int	mlx_print_char_to_image(t_writer *w, t_image *image, char ch, t_point pos)
{
	t_image		*src;
	t_symbol	*symbol;

	if (!w)
		return (0);
	symbol = w->symbols;
	while (symbol && symbol->symbol != ch)
		symbol = symbol->next;
	if (!symbol)
		return (0);
	src = symbol->image;
	img_put_img(image, src, pos, 0);
	return (symbol->image->width);
}

int	mlx_print(t_writer *w, void *win, char *str, t_point pos)
{
	int		counter;
	float	start_x;

	if (!w || !str)
		return (0);
	counter = 0;
	start_x = pos.x;
	while (str[counter])
	{
		if (str[counter] == ' ')
			pos.x += w->space;
		else
			pos.x += mlx_print_char(w, win, str[counter], pos);
		counter++;
	}
	return (pos.x - start_x);
}

int	mlx_print_to_image(t_writer *w, t_image *image, char *str, t_point pos)
{
	int		counter;
	float	start_x;

	if (!w || !str)
		return (0);
	counter = 0;
	start_x = pos.x;
	while (str[counter])
	{
		if (str[counter] == ' ')
			pos.x += w->space;
		else
			pos.x += mlx_print_char_to_image(w, image, str[counter], pos);
		counter++;
	}
	return (pos.x - start_x);
}
