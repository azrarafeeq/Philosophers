/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:58:01 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/26 18:11:44 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_dinner(t_main *dinner, int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc == 5)
		dinner->amt_to_eat = 0;
	else
		dinner->amt_to_eat = ft_atoi(argv[5]);
	dinner->amt_of_philo = ft_atoi(argv[1]);
	dinner->time_to_die = ft_atoi(argv[2]);
	dinner->time_to_eat = ft_atoi(argv[3]);
	dinner->time_to_sleep = ft_atoi(argv[4]);
	memset(dinner->forks, 0, dinner->amt_of_philo);
	dinner->routine_start = get_current_time();
	dinner->routine_end = 0;
	while (++i < dinner->amt_of_philo)
		pthread_mutex_init(&(dinner->mutex_fork[i]), NULL);
	pthread_mutex_init(&(dinner->print_mutex), NULL);
	pthread_mutex_init(&(dinner->time_mutex), NULL);
	pthread_mutex_init(&(dinner->finish_mutex), NULL);
	//initialize other mutexes
}

void	init_philo(t_main *din)
{
	int		id;

	id = -1;
	while (++id < din->amt_of_philo)
	{
		din->philos[id].id = id + 1;
		din->philos[id].last_ate = 0;
		din->philos[id].right_fork = id;
		if (id == 0)
			din->philos[id].left_fork = din->amt_of_philo - 1;
		else
			din->philos[id].left_fork = id - 1;
		din->philos[id].right_mutex = din->mutex_fork[id];
		if (id == 1)
			din->philos[id].left_mutex = din->mutex_fork[din->amt_of_philo - 1];
		else
			din->philos[id].left_mutex = din->mutex_fork[id - 1];
		din->philos[id].current_time = 0;
		din->philos[id].eat_start = 0;
		din->philos[id].last_ate = 0;
		din->philos[id].main = din;
	}
}
