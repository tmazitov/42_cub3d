/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:18:10 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 20:19:06 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_INVENTORY_H
# define PLAYER_INVENTORY_H

# include "../../../utils/image/image.h"
# include "../../../utils/libft/libft.h"
# include "../../../utils/mlx_font_print/mlx_font_print.h"
# include "../../items/items.h"

# define INV_CELL_SIZE 64
# define INV_CELL_PADDING 8
# define INV_BORDER_SIZE 4
# define INV_BORDER_COLOR 0x0042c79a
# define INV_BORDER_RADIUS 4
# define INV_BACKGROUND_COLOR 0x00555955
# define INV_PADDING 10

typedef struct s_health_bar
{
	int					max;
	int					current;
	t_image				*image;
}						t_health_bar;

typedef struct s_inv_images
{
	t_image				*bullet_image;
	t_image				*slot_image;
	t_image				*active_slot_image;
	t_image				*pistol_image;
}						t_inv_images;

typedef struct s_inventory
{
	t_point				*pos;
	int					size;
	int					bullets;
	int					active_item;
	t_item_collection	*slots;
	t_image				*image;
	int					update_count;
	t_health_bar		*health_bar;
}						t_inventory;

t_inventory				*make_inventory(int size);
int						inv_set_sizes(void *mlx, t_inventory *inventory,
							t_rectangle rect);
void					inv_update_image(t_inventory *inv,
							int player_update_count, t_inv_images images,
							t_writer *writer);
void					*free_inventory(t_inventory *inventory);

int						bullets_message_size(t_inventory *inventory);

t_health_bar			*make_health_bar(int max);
int						hb_new_image(void *mlx, t_health_bar *bar, int width,
							int height);
int						hb_add_damage(t_health_bar *bar, int damage);
void					*free_health_bar(t_health_bar *bar);
t_item					*inv_get_active_item(t_inventory *inventory);

#endif