/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_anime_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 05:51:17 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/25 23:00:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

static t_anime_frame	*get_last_frame(t_anime *anime)
{
	t_anime_frame	*last_frame;
	int				counter;

	counter = 0;
	last_frame = anime->frames;
	while (counter < anime->frame_count - 1)
	{
		last_frame = last_frame->next;
		counter++;
	}
	return (last_frame);
}

/// @brief Provide the ability to add a frame to the animation.
/// @param anime animation instance
/// @param image image to make new frame
/// @param duration new frame duration
/// @return success -> 1 , failure -> 0
int	anime_add_frame(t_anime *anime, t_image *image, int duration)
{
	t_anime_frame	*frame;

	frame = malloc(sizeof(t_anime_frame));
	if (!frame)
		return (0);
	frame->image = image;
	frame->duration = duration;
	frame->next = NULL;
	if (!anime->frames)
	{
		anime->frames = frame;
		anime->current_frame = frame;
		frame->next = anime->frames;
	}
	else
	{
		get_last_frame(anime)->next = frame;
		frame->next = anime->frames;
	}
	anime->frame_count++;
	anime->duration += duration;
	return (1);
}

/// @brief Return the current frame image of the animation.
/// @param anime animation
/// @return Current frame image
t_image	*anime_current_frame(t_anime *anime)
{
	if (!anime || !anime->frames)
		return (NULL);
	if (anime->current_frame->duration == anime->iter)
	{
		anime->current_frame = anime->current_frame->next;
		anime->iter = 0;
	}
	anime->iter++;
	return (anime->current_frame->image);
}

void	*free_frame(t_anime_frame *frame)
{
	if (!frame)
		return (NULL);
	if (IS_FREE_FRAME_IMAGE && frame->image)
		free_image(frame->image);
	free(frame);
	return (NULL);
}
