/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:53:21 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/02 10:51:29 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	running_threads(int action, pthread_t thread)
{
	static pthread_t	threads[MAX_THREADS];
	static int			i = 0;
	int					tmp;

	if (i >= MAX_THREADS)
		i = 0;
	if (action == ADD)
		threads[i++] = thread;
	else if (action == STOP)
	{
		tmp = 0;
		while (tmp < i)
			pthread_join(threads[tmp++], NULL);
	}
	else if (action == INIT)
	{
		tmp = 0;
		while (tmp < MAX_THREADS)
			threads[tmp++] = 0;
	}
}

bool	quit_program(t_data *data)
{
	bool	quit;

	if (pthread_mutex_lock(&data->quit.mutex) != 0)
		return (printf(RED"Error init mutex\n"RESET), exit(1), true);
	quit = data->quit.flag;
	if (pthread_mutex_unlock(&data->quit.mutex) != 0)
		return (printf(RED"Error init mutex\n"RESET), exit(1), true);
	return (quit);
}

void	set_exit_flag(t_data *data)
{
	if (pthread_mutex_lock(&data->quit.mutex) != 0)
		return (printf(RED"Error init mutex\n"RESET), exit(1));
	data->quit.flag = true;
	if (pthread_mutex_unlock(&data->quit.mutex) != 0)
		return (printf(RED"Error init mutex\n"RESET), exit(1));
}
