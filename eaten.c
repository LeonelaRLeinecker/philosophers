/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eaten.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:49:56 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:22 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	int		left_idx;
	int		right_idx;
	t_data	*data;

	data = philo->t_data;
	left_idx = philo->id - 1;
	right_idx = philo->id % data->num_of_philos;
	if (left_idx < right_idx)
	{
		pthread_mutex_lock(&data->forks[left_idx]);
		pthread_mutex_lock(&data->forks[right_idx]);
	}
	else
	{
		pthread_mutex_lock(&data->forks[right_idx]);
		pthread_mutex_lock(&data->forks[left_idx]);
	}
	print_state(philo, "has taken a fork");
	print_state(philo, "has taken a fork");
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat_philo(t_philo *philo)
{
	take_forks(philo);
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->t_data->death_mutex);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->t_data->death_mutex);
	smart_sleep(philo->t_data->time_to_eat, philo->t_data);
	put_forks(philo);
}
