/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:15:08 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/03 20:05:51 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi_long(const char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	while (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	valid_input(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!valid_input(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parse_and_init(int argc, char **argv, t_data *data)
{
	if (!validate_args(argc, argv))
	{
		error_exit("Wrong argument");
	}
	data->number_of_philosophers = ft_atoi_long(argv[1]);
	data->time_to_die = ft_atoi_long(argv[2]);
	data->time_to_eat = ft_atoi_long(argv[3]);
	data->time_to_sleep = ft_atoi_long(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi_long(argv[5]);
	else
		data->must_eat_count = -1;
	if (data->number_of_philosophers <= 0
		|| data->number_of_philosophers > 200
		|| data->time_to_die <= 0 || data->time_to_die > 1000000
		|| data->time_to_eat <= 0 || data->time_to_eat > 1000000
		|| data->time_to_sleep <= 0 || data->time_to_sleep > 1000000
		|| (argc == 6 && data->must_eat_count <= 0))
		exit(1);
	data->philos = NULL;
	data->forks = NULL;
	data->someone_die = 0;
	data->number_of_forks = data->number_of_philosophers;
}
