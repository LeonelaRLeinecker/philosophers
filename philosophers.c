/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:29:38 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/09 21:42:13 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philosophers(t_data *data)
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

static void	eat_even_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->t_data->death_mutex);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->t_data->death_mutex);
	smart_sleep(philo->t_data->time_to_eat, philo->t_data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	eat_odd_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->t_data->death_mutex);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->t_data->death_mutex);
	smart_sleep(philo->t_data->time_to_eat, philo->t_data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/*static void take_forks(t_philo *philo)
{
    t_data *data;
    int left_idx;
    int right_idx;

    data = philo->t_data;
    left_idx = philo->id - 1;
    right_idx = philo->id % data->number_of_philosophers;
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

static void put_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

static void eat_philo(t_philo *philo)
{
    take_forks(philo);
    print_state(philo, "is eating");
    pthread_mutex_lock(&philo->t_data->death_mutex);
    philo->last_meal = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->t_data->death_mutex);
    smart_sleep(philo->t_data->time_to_eat, philo->t_data);
    put_forks(philo);
}*/
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
	// if (philo->id % 2 != 0)
	// 	usleep((philo->t_data->time_to_sleep / 2) * 1000);
	// if (philo->t_data->number_of_philosophers > 3)
	// 	usleep((philo->id % 3) * 10);
	if (data->number_of_philosophers % 2 == 1)
    {
        // Número impar: impares esperan más
        if (philo->id % 2 != 0)
            usleep(data->time_to_eat * 1000 / 2);  // 100ms para 5 filósofos
        else
            usleep(data->time_to_eat * 1000 / 4);  // 50ms
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
		if (philo->id % 2 == 0)
		{
			// usleep(100);
			eat_even_philo(philo);
		}
		else
		{
			// usleep(100);
			eat_odd_philo(philo);
		}
		// eat_philo(philo);
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
	if (data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		smart_sleep(data->time_to_die, data);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	/*if (philo->id % 2 == 0)
		usleep(1000);*/
	run_philo_loop(philo);
	return (NULL);
}

/*void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->t_data;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_die)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		if (philo->id % 2 == 0)
			eat_even_philo(philo);
		else
			eat_odd_philo(philo);
		print_state(philo, "is sleeping");
		smart_sleep(data->time_to_sleep, data);
		print_state(philo, "is thinking");
	}
	return (NULL);
}*/
