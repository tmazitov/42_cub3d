/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ambient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:16:43 by tmazitov          #+#    #+#             */
/*   Updated: 2024/08/28 20:16:56 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*ambient_sound_func(void *arg)
{
	t_ambient_sound	*ambient_sound;
	char			*sound_path;
	ma_result		result;
	ma_engine		engine;

	ambient_sound = (t_ambient_sound *)arg;
	sound_path = ambient_sound->sound_path;
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS)
		return (NULL);
	result = ma_engine_play_sound(&engine, sound_path, NULL);
	if (result != MA_SUCCESS)
	{
		ma_engine_uninit(&engine);
		return (NULL);
	}
	while (1)
	{
		if (ambient_sound->game->blocker == 1)
			break ;
		usleep(500000);
	}
	ma_engine_uninit(&engine);
	return (NULL);
}

void	ambient_sound(t_game *game, char *sound_path)
{
	t_ambient_sound	*ambient_sound;
	pthread_t		sound_thread;

	ambient_sound = malloc(sizeof(t_ambient_sound));
	ambient_sound->game = game;
	ambient_sound->sound_path = sound_path;
	pthread_create(&sound_thread, NULL, ambient_sound_func, ambient_sound);
	pthread_detach(sound_thread);
}
