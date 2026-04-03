/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:01:31 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/03 20:05:43 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_forks);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->number_of_forks)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	if (!init_forks(data))
		return (0);
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
	{
		cleanup_data(data);
		return (0);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		cleanup_data(data);
		return (0);
	}
	return (1);
}
