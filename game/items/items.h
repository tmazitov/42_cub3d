/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:06:01 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 22:31:25 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

# include <stdlib.h>

# define PISTOL_DAMAGE 20

// sofa : timur and khisravbek can do the best cub 3d ever!!!
typedef enum e_item_type
{
	BULLET = 1,
	PISTOL = 2,
}					t_item_type;

typedef struct s_item
{
	t_item_type		type;
	int				amount;
}					t_item;

typedef struct s_item_collection
{
	t_item			**items;
	int				size;
}					t_item_collection;

t_item				*make_item(t_item_type type, int amount);
void				*free_item(t_item *item);

t_item_collection	*make_item_collection(int size);
int					item_collection_add_item(t_item_collection *collection,
						t_item_type type, int amount);
void				*free_item_collection(t_item_collection *collection);

#endif