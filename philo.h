/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:39:56 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/26 17:43:24 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	unsigned int	eat_start;
	unsigned int	last_ate;
	unsigned int	current_time;
	int				right_fork;
	int				left_fork;
	int				times_eaten;
	pthread_mutex_t	left_mutex;
	pthread_mutex_t	right_mutex;
	struct s_main	*main;
}				t_philo;

typedef struct s_main{
	int				amt_of_philo;
	int				forks[200];
	t_philo			philos[200];
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	pthread_mutex_t	mutex_fork[200];
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	finish_mutex;
	useconds_t		routine_start;
	int				routine_end;
	int				amt_to_eat;
	//extra mutexes
}				t_main;

void		init_dinner(t_main *dinner, int argc, char **argv);
void		init_philo(t_main *dinner);
int			forks_available(t_philo *philo);

int			ft_atoi(const char *str);
void		ws_and_sign_check(const char *str, int *i, int *ve);

useconds_t	get_current_time(void);
void		*routine(void *arg);
int			eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		millie_sleep(useconds_t routine_time, t_philo *philo);

void		checker(t_main *dinner, int argc);

#endif