/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:45:10 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/14 18:32:47 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (i < data->number_of_forks)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	if (data->philos)
		free(data->philos);
}

void	print_state(t_philo *philo, const char *s)
{
	long	timestamp;

	pthread_mutex_lock(&philo->t_data->death_mutex);
	if (philo->t_data->someone_die)
	{
		pthread_mutex_unlock(&philo->t_data->death_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->t_data->write_mutex);
	timestamp = get_current_time() - philo->t_data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, s);
	pthread_mutex_unlock(&philo->t_data->write_mutex);
	pthread_mutex_unlock(&philo->t_data->death_mutex);
}

void	smart_sleep(long time_in_ms, t_data *data)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time_in_ms)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_die)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(100);
	}
}
