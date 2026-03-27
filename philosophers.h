/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:15:32 by lleineck          #+#    #+#             */
/*   Updated: 2026/03/27 18:51:43 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>



typedef struct s_data
{
	int				number_of_philosophers;
	int				number_of_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				someone_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				last_meal;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_timeval
{
	long	tv_sec;
	long	tv_usec;
}	t_timeval;

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_atoi(const char *s);
int		validate_args(int argc, char **argv);
void	parse_and_init(int argc, char **argv, t_data *t_data);
int		init_mutexes(t_data *t_data);
int		init_mutexes(t_data *t_data);
void	destroy_mutexes(t_data *t_data);





#endif