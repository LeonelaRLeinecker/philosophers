/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:15:32 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/03 20:03:12 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	t_data			*t_data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_data
{
	long			number_of_philosophers;
	long			number_of_forks;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat_count;
	int				someone_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_data;

typedef struct s_timeval
{
	long	tv_sec;
	long	tv_usec;
}	t_timeval;

long	ft_atoi_long(const char *s);
int		validate_args(int argc, char **argv);
void	parse_and_init(int argc, char **argv, t_data *data);
int		init_mutexes(t_data *tata);
void	error_exit(const char *error);
long	get_current_time(void);
void	cleanup_data(t_data *data);
void	print_state(t_philo *philo, const char *s);
void	smart_sleep(long time_in_ms, t_data *data);
int		init_philosophers(t_data *data);
void	*philo_routine(void *arg);
int		check_death(t_data *data, long long now);
int		check_meals(t_data *data);
void	*hecate(void *arg);
#endif