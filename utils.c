/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:45:10 by lleineck          #+#    #+#             */
/*   Updated: 2026/03/31 18:11:45 by lleineck         ###   ########.fr       */
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
	t_timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	cleanup_data(t_data *t_data)
{
	int	i;

	i = 0;
	if (!t_data)
		return ;
	while (i < t_data->number_of_forks)
	{
		pthread_mutex_destroy(&t_data->forks[i]);
		i++;
	}
	if (t_data->forks)
		free(t_data->forks);
	pthread_mutex_destroy(&t_data->write_mutex);
	pthread_mutex_destroy(&t_data->death_mutex);
	if (t_data->philos)
		free(t_data->philos);
}



