/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:39:56 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/07 15:16:53 by arafeeq          ###   ########.fr       */
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

typedef struct s_ph
{
	pthread_t		ph;
	int				id;
	unsigned int	last_ate;
	unsigned int	current_time;
	int				right_fork;
	int				left_fork;
	int				sl;
	int				sr;
	int				times_eaten;
	struct sm		*m;
}				t_ph;

typedef struct sm{
	int				amt_of_ph;
	int				forks[200];
	int				sign[200];
	t_ph			m_p[200];
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	pthread_mutex_t	mutex[200];
	pthread_mutex_t	sm[200];
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t	times_eaten_mutex;
	pthread_mutex_t	last_ate_mutex;
	unsigned int	routine_start;
	int				routine_end;
	int				argc;
	int				amt_to_eat;
}				t_m;

void			init_dinner(t_m *dinner, int argc, char **argv);
void			init_ph(t_m *dinner);
void			ph_thread_create(t_m *dinner);
int				forks_available(t_ph *ph);

int				not_digit(int argc, char **argv);
int				ft_atoi(const char *str);
void			ws_and_sign_check(const char *str, int *i, int *ve);

void			*routine(void *arg);
void			eating(t_ph *ph);
void			sleeping(t_ph *ph);
void			thinking(t_ph *ph);
void			millie_sleep(unsigned int routine_time, t_ph *ph);

void			print_message(t_ph *ph, int flag, char *str);
void			print_death(t_m **din, int i, unsigned int time);
void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_putnbr(int n);

int				ph_starvation(t_m *dinner);
void			main_checker(t_m *dinner, int argc);

unsigned int	get_current_time(void);

#endif