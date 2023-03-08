/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:58:01 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/08 13:15:26 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_dinner(t_m *dinner, int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc == 5)
		dinner->amt_to_eat = 0;
	else
		dinner->amt_to_eat = ft_atoi(argv[5]);
	dinner->amt_of_ph = ft_atoi(argv[1]);
	dinner->time_to_die = ft_atoi(argv[2]);
	dinner->time_to_eat = ft_atoi(argv[3]);
	dinner->time_to_sleep = ft_atoi(argv[4]);
	dinner->argc = argc;
	memset(dinner->forks, 0, dinner->amt_of_ph);
	memset(dinner->sign, 0, dinner->amt_of_ph);
	dinner->routine_start = get_current_time();
	dinner->routine_end = 0;
	while (++i < dinner->amt_of_ph)
		pthread_mutex_init(&(dinner->mutex[i]), NULL);
	i = -1;
	while (++i < dinner->amt_of_ph)
		pthread_mutex_init(&(dinner->sm[i]), NULL);
	pthread_mutex_init(&(dinner->print_mutex), NULL);
	pthread_mutex_init(&(dinner->finish_mutex), NULL);
	pthread_mutex_init(&(dinner->times_eaten_mutex), NULL);
	pthread_mutex_init(&(dinner->last_ate_mutex), NULL);
}

void	init_ph(t_m *din)
{
	int		id;

	id = -1;
	while (++id < din->amt_of_ph)
	{
		din->m_p[id].id = id + 1;
		din->m_p[id].last_ate = 0;
		din->m_p[id].right_fork = id;
		din->m_p[id].sr = id;
		din->m_p[id].left_fork = (id + 1) % din->amt_of_ph;
		din->m_p[id].sl = (id + 1) % din->amt_of_ph;
		din->m_p[id].m = din;
	}
}

void	ph_thread_create(t_m *dinner)
{
	int		i;

	i = 0;
	while (i < dinner->amt_of_ph)
	{
		pthread_create(&(dinner->m_p[i].ph),
			NULL, &routine, &(dinner->m_p[i]));
		usleep(250);
		i++;
	}
}

unsigned int	get_current_time(void)
{
	unsigned int		millie_seconds;
	struct timeval		time;

	gettimeofday(&time, NULL);
	millie_seconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (millie_seconds);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
