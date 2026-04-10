/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:29:38 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/10 20:01:26 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].t_data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[
			(i + 1) % data->num_of_philos];
		i++;
	}
	return (1);
}

void	*handle_single_philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	usleep(philo->t_data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static void	run_philo_loop(t_philo *philo)
{
	t_data	*data;

	data = philo->t_data;
	if (data->num_of_philos > 50 && data->num_of_philos % 2 == 1)
	{
		if (philo->id % 2 != 0)
			usleep(data->time_to_eat * 1000);
		else
			usleep(data->time_to_eat * 1000 / 2);
	}
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_die)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		eat_philo(philo);
		print_state(philo, "is sleeping");
		smart_sleep(data->time_to_sleep, data);
		print_state(philo, "is thinking");
		usleep(100);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->t_data;
	if (data->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		smart_sleep(data->time_to_die, data);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	run_philo_loop(philo);
	return (NULL);
}
