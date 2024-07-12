/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshamsid <kshamsid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:15:53 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/12 16:31:41 by kshamsid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../game.h"
# include "../../utils/image/image.h"

void	render_scene(t_game *game);
int		render_hook(t_game *game);
void	render_minimap(t_game *game);
#endif // RENDER_H