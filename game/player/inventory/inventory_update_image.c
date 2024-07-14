/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_update_image.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:07:41 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/15 01:36:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inventory.h"

void	inv_draw_border(t_inventory *inv)
{
	t_image_border	border;

	border.size = INV_BORDER_SIZE;
	border.color = INV_BORDER_COLOR;
	border.radius = INV_BORDER_RADIUS;
	img_paint_border(inv->image, border);
}

void	inv_draw_background(t_inventory	*inv)
{
	t_rectangle	rect;

	rect.start.x = INV_BORDER_SIZE;
	rect.start.y = INV_BORDER_SIZE;
	rect.width = inv->image->width - INV_BORDER_SIZE * 2;
	rect.height = inv->image->height - INV_BORDER_SIZE * 2;
	img_put_rectangle(inv->image, rect, INV_BACKGROUND_COLOR);
}

void	inv_draw_bullets(t_inventory *inv, t_image	*bullet_image, t_writer *writer)
{
	char	*str_value;
	t_point	pos;

	if (!bullet_image)
		return ;
	str_value = ft_itoa(inv->bullets);
	if (!str_value)
		return ;
	pos.x = INV_BORDER_SIZE + INV_PADDING;
	pos.y = INV_BORDER_SIZE + INV_PADDING;
	if (inv->health_bar->image)
	{
		pos.y += 20;
		img_put_img(inv->image, inv->health_bar->image, pos, 0);
		pos.y -= 20;
		pos.x += inv->health_bar->image->width + INV_CELL_PADDING;	
	}
	pos.y += 8;
	pos.x += mlx_print_to_image(writer, inv->image, str_value, pos) + INV_CELL_PADDING;
	pos.y -= 8;
	img_put_img(inv->image, bullet_image, pos, 0);
	free(str_value);
}

void	inv_draw_slots(t_inventory *inv, t_image *slot_image)
{
	t_point	pos;
	int		counter;

	if (!slot_image)
		return ;
	pos.x = INV_BORDER_SIZE + INV_PADDING;
	pos.y = INV_BORDER_SIZE + INV_PADDING + INV_CELL_SIZE + INV_CELL_PADDING;
	counter = 0;
	while (counter < inv->size)
	{
		img_put_img(inv->image, slot_image, pos, 0);
		pos.x += INV_CELL_SIZE + INV_CELL_PADDING;
		counter++;
	}
}

void	inv_update_image(t_inventory *inv, int player_update_count, \
	t_image	*bullet_image, t_image	*slot_image, t_writer *writer)
{
	if (player_update_count == inv->update_count)
		return ;
	inv->update_count = player_update_count;
	img_clear(inv->image);
	inv_draw_background(inv);
	inv_draw_border(inv);
	inv_draw_slots(inv, slot_image);
	inv_draw_bullets(inv, bullet_image, writer);
}