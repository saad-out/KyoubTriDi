/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:52:31 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/02 12:47:24 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	*loop_sound(void *arg)
{
	t_data	*data;

	data = get_data(NULL);
	while (!quit_program(data))
		play_mp3(arg);
	return (NULL);
}

void	theme_sound(char *mp3)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, loop_sound, (void *)mp3) != 0)
		return (printf(RED"error creating thread\n"RESET), (void)0);
	running_threads(ADD, thread);
}

void	play_sound_bg(char *mp3)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, play_mp3, (void *)mp3) != 0)
		return (printf(RED"error creating thread\n"RESET), (void)0);
	running_threads(ADD, thread);
}
