/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:02:31 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/08 19:27:10 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	setup_data(int argc, char **argv, t_data *data)
{
	parse_and_init(argc, argv, data);
	if (!init_mutexes(data))
		return (0);
	if (!init_philosophers(data))
		return (0);
	data->start_time = get_current_time();
	return (1);
}

/*static void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;
	void		*(*philo_func)(void *) = philo_routine;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			error_exit("Thread creation failed");
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, hecate, data) != 0)
		error_exit("Monitor thread creation failed");
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}*/

static void	create_philos_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].last_meal = data->start_time;
		if (data->number_of_philosophers == 1)
		{
			if (pthread_create(&data->philos[i].thread, NULL,
					handle_single_philosopher, &data->philos[i]) != 0)
				error_exit("Thread creation failed");
		}
		else
		{
			if (pthread_create(&data->philos[i].thread, NULL,
					philo_routine, &data->philos[i]) != 0)
				error_exit("Thread creation failed");
		}
		i++;
	}
}

static void	join_philos_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static void	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;

	create_philos_threads(data);
	if (pthread_create(&monitor_thread, NULL, hecate, data) != 0)
		error_exit("Monitor thread creation failed");
	join_philos_threads(data);
	pthread_join(monitor_thread, NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!validate_args(argc, argv))
		error_exit("Wrong type or number of arguments.");
	data = malloc(sizeof(t_data));
	if (!data)
		error_exit("Memory allocation failed for data");
	if (!setup_data(argc, argv, data))
	{
		cleanup_data(data);
		free(data);
		error_exit("Initialization failed");
	}
	start_simulation(data);
	cleanup_data(data);
	free(data);
	return (0);
}
