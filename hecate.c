/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hecate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:36:30 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/09 19:27:44 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*int	check_death(t_data *data, long long now)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (now - data->philos[i].last_meal >= data->time_to_die)
		{
			data->someone_die = 1;
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_lock(&data->write_mutex);
			printf("%lld %d died\n", now - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->write_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
	return (0);
}*/

int	check_death(t_data *data)
{
	int			i;
	long long	now;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->death_mutex);
		now = get_current_time();
		if (now - data->philos[i].last_meal >= data->time_to_die)
		{
			data->someone_die = 1;
			pthread_mutex_lock(&data->write_mutex);
			printf("%lld %d died\n",
				now - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->write_mutex);
			pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
	return (0);
}


int	check_meals(t_data *data)
{
	int	i;
	int	full_count;

	i = 0;
	full_count = 0;
	if (data->must_eat_count <= 0)
		return (0);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat_count)
			full_count++;
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
	if (full_count != data->number_of_philosophers)
		return (0);
	pthread_mutex_lock(&data->death_mutex);
	data->someone_die = 1;
	pthread_mutex_lock(&data->write_mutex);
	printf("All philosophers have eaten enough\n");
	pthread_mutex_unlock(&data->write_mutex);
	pthread_mutex_unlock(&data->death_mutex);
	return (1);
}

/*void	*hecate(void *arg)
{
	long long	now;
	t_data		*data;

	data = (t_data *)arg;
	while (1)
	{
		now = get_current_time();
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_die)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		if (check_death(data, now) || check_meals(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}*/

void	*hecate(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) || check_meals(data))
			break ;
		usleep(100);
	}
	return (NULL);
}

