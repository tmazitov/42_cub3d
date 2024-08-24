/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treasure.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:29:48 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/24 17:26:11 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREASURE_H
# define TREASURE_H

# include "../../../utils/geometry/geometry.h"

typedef struct s_treasure
{
	t_point	*pos;
	t_point	*center;
}			t_treasure;

t_treasure	*make_treasure(float x, float y);
void		*free_treasure(t_treasure *treasure);

#endif
