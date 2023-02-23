/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:39:56 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/23 18:19:37 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

typedef struct s_main{
	int				amt_of_philo;
	struct s_philo	*philos;
	pthread_mutex_t	*mutex_fork;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	get_time;
	//extra mutexes
	useconds_t		routine_start;
	int				routine_end;
	int				amt_to_eat;
}				t_main;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	unsigned int	last_ate;
	int				*right_fork;
	int				left_fork;
	pthread_mutex_t	*right_mutex;
	pthread_mutex_t	left_mutex;
	t_main			*main;
	struct s_philo	*next;
}				t_philo;

void		init_dinner(t_main *dinner, int argc, char **argv);
void		init_philo(t_main *dinner, t_philo *philo, int id);
void		philo_list(t_philo **philos, t_main *dinner);
void		eating(t_philo *philo);
void		ws_and_sign_check(const char *str, int *i, int *ve);
void		print_message(useconds_t time, int id, int flag);

int			ft_atoi(const char *str);
int			number_length(int n);

char		*number_conversion(int num, char *str, int len);
char		*ft_itoa(int n);

useconds_t	get_current_time(void);
void		millie_sleep(useconds_t routine_time);

#endif