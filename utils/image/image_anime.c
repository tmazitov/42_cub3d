/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_anime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 05:45:04 by tmazitov          #+#    #+#             */
/*   Updated: 2024/07/28 06:52:47 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	init_anime(t_anime *anime)
{
	anime->frames = NULL;
	anime->current_frame = NULL;
	anime->frame_count = 0;
	anime->iter = 0;
	anime->duration = 0;
}

t_anime	*make_anime()
{
	t_anime	*anime;

	anime = malloc(sizeof(t_anime));
	if (!anime)
		return (NULL);
	init_anime(anime);
	return (anime);
}

/// @brief Provide the ability to copy animation with all frames. 
/// @param anime animation to copy
/// @return Copied animation
t_anime	*anime_copy(t_anime *anime)
{
	int		counter;
	t_anime	*copy;
	t_anime_frame	*frame;

	if (!anime)
		return (NULL);
	counter = 0;
	copy = make_anime();
	if (!copy)
		return (NULL);
	frame = anime->frames;
	while (counter < anime->frame_count)
	{
		if (!anime_add_frame(copy, frame->image, frame->duration))
			return (free_anime(copy));
		frame = frame->next;	
		counter++;
	}
	return (copy);
}

void	*free_anime(t_anime *anime)
{
	t_anime_frame	*frame;
	t_anime_frame	*next;
	int	counter;

	if (!anime)
		return (NULL);
	if (anime->frames)
	{
		counter = 0;
		frame = anime->frames;
		while (counter < anime->frame_count)
		{
			next = frame->next;
			free_frame(frame);
			frame = next;
			counter++;
		}
	}
	free(anime);
	return (NULL);
}