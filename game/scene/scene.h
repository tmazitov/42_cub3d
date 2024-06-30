/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:30:51 by tmazitov          #+#    #+#             */
/*   Updated: 2024/06/30 14:34:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stdlib.h>
# include "../minimap/minimap.h"

typedef struct s_scene
{
	t_minimap	*minimap;
}			t_scene;

t_scene	*make_scene(void *mlx);
void	*free_scene(t_scene *scene);

#endif // SCENE_H