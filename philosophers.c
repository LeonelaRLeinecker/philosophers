/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:29:38 by lleineck          #+#    #+#             */
/*   Updated: 2026/03/31 20:08:09 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philosophers(struct s_data *t_data)
{
	int	i;

	t_data->philos = malloc(sizeof(t_philo) * t_data->number_of_philosophers);
	if (!t_data->philos)
		return (0);
	i = 0;
	while (i < t_data->number_of_philosophers)
	{
		t_data->philos[i].id = i + 1;
		t_data->philos[i].meals_eaten = 0;
		t_data->philos[i].last_meal = 0;
		t_data->philos[i].t_data = t_data;
		t_data->philos[i].left_fork = &t_data->forks[i];
		t_data->philos[i].right_fork = &t_data->forks[
			(i + 1) % t_data->number_of_philosophers];
		i++;
	}
	return (1);
}


void	philo_routine(struct s_data *t_data, struct s_philo *t_philo)
{
	int		i;
	long	current_time;

	i = 0;
	if (t_data->number_of_philosophers == 1)
	{
		locked(t_philo->left_fork);
		current_time = t_data->time_to_die;
		return (0);
	}
	current_time = get_current_time();
	while (t_data->someone_die == 0)
	{
		t_data->write_mutex("thinking");
		if (t_philo->id % 2 == 0)
		{
			locked(t_philo->left_fork);
			t_data->write_mutex("taking left fork");
			locked(t_philo->right_fork);
			t_data->write_mutex("taking rigt fork");
		}
		else
		{
			locked(t_philo->right_fork);
			t_data->write_mutex("taking right fork");
			locked(t_philo->left_fork);
			t_data->write_mutex("taking left fork");
		}
		
	}
}




