/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:01:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/14 13:58:08 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_INVENTORY_H
# define PLAYER_INVENTORY_H

# include "../../../utils/image/image.h"
# include "../../items/items.h"


typedef struct s_inventory
{
	int					size;
	int					bullets;
	t_item				*active_item;
	t_item_collection	*slots;
}	t_inventory;

t_inventory	*make_inventory(int size);
void		*free_inventory(t_inventory *inventory);

#endif