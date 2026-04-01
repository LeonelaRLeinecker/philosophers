/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:29:38 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/01 19:20:05 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philosophers(struct s_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].t_data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[
			(i + 1) % data->number_of_philosophers];
		i++;
	}
	return (1);
}


void	philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->t_data;
	if (data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		usleep(data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	current_time = get_current_time();
	while (t_data->someone_die == 0)
	{
		t_data->write_mutex("thinking");
		if (t_philo->id % 2 == 0)
		{
			locked(t_philo->left_fork);
			locked(t_data->write_mutex);
			printf("taking left fork\n");
			locked(t_philo->right_fork);
			locked(t_data->write_mutex)
			printf("taking rigt fork\n");
			*t_data->write_mutex("Philo id [%d], is eating");
		}
		else
		{
			locked(t_philo->right_fork);
			t_data->write_mutex("taking right fork");
			locked(t_philo->left_fork);
			t_data->write_mutex("taking left fork");
			*t_data->write_mutex("Philo id [%d], is eating");
		}
	}
}




