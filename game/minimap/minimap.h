/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:20:45 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 17:10:41 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include <stdlib.h>
# include <math.h>
# include "../../utils/image/image.h"

# define MINIMAP_BORDER_COLOR 0x0042c79a
# define MINIMAP_BORDER_RADIUS 10
# define MINIMAP_BORDER_SIZE 8
# define MINIMAP_POS_X 10
# define MINIMAP_POS_Y 10

typedef struct s_minimap
{
	t_image		*image;
	int			height;
	int			width;
}			t_minimap;

t_minimap	*make_minimap(void *mlx, int width, int height);
void		*free_minimap(t_minimap *map);

void		minimap_update(t_minimap *minimap);
void		minimap_update_image(t_minimap *minimap);

# endif