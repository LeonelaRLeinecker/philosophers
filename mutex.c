/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:01:31 by lleineck          #+#    #+#             */
/*   Updated: 2026/03/26 18:17:36 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_data *t_data)
{
	int	i;

	t_data->forks = malloc(sizeof(pthread_mutex_t) * t_data->number_of_forks);
	if (!t_data->forks)
		return (0);
	i = 0;
	while (i < t_data->number_of_forks)
	{
		if (pthread_mutex_init(&t_data->write_mutex, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&t_data->write_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&t_data->death_mutex, NULL) != 0)
		return (0);
	return (1);
}

void	destroy_mutexes(t_data *t_data)
{
	int	i;

	i = 0;
	while (i < t_data->number_of_forks)
		pthread_mutex_destroy(&t_data->forks[i++]);
	pthread_mutex_destroy(&t_data->write_mutex);
	pthread_mutex_destroy(&t_data->death_mutex);
	free(t_data->forks);
}

