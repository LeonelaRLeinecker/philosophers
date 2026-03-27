/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:29:38 by lleineck          #+#    #+#             */
/*   Updated: 2026/03/27 19:01:24 by lleineck         ###   ########.fr       */
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
		t_data->philos[i].data = t_data;
		t_data->philos[i].left_fork = &t_data->forks[i];
		t_data->philos[i].right_fork = &t_data->forks[
			(i + 1) % t_data->number_of_philosophers];
		i++;
	}
	return (1);
}

int	get_current_time(struct s_timeval *t_timeval)
{
	int	current_time;

	t_timeval = gettimeofday();
	current_time = (t_timeval->tv_sec * 1000) + (t_timeval->tv_usec / 1000);
	return (current_time);
}

void	philo_routine(struct s_data *t_data, struct s_philo *t_philo)
{
	if ((get_current_time(t_timeval) - t_philo->last_meal) < t_data->time_to_die)
	{
		
	} 
	

}



