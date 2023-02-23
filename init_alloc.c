/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:58:01 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/23 18:20:29 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_dinner(t_main *dinner, int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc == 5)
		dinner->amt_to_eat = 0;
	else
		dinner->amt_to_eat = ft_atoi(argv[5]);
	dinner->amt_of_philo = ft_atoi(argv[1]);
	dinner->time_to_die = ft_atoi(argv[2]);
	dinner->time_to_eat = ft_atoi(argv[3]);
	dinner->time_to_sleep = ft_atoi(argv[4]);
	dinner->philos = malloc(sizeof(pthread_t) * dinner->amt_of_philo);
	dinner->mutex_fork = malloc(sizeof(pthread_mutex_t) * dinner->amt_of_philo);
	dinner->routine_end = 0;
	while (i < dinner->amt_of_philo)
	{
		if (pthread_mutex_init(&(dinner->mutex_fork[i]), NULL) != 0)
			printf("Error : Couldn't create mutex\n");
		i++;
	}
	pthread_mutex_init(&(dinner->print_mutex), NULL);
	pthread_mutex_init(&(dinner->get_time), NULL);
	//initialize other mutexes
}

void	init_philo(t_main *dinner, t_philo *philo, int id)
{
	philo->id = id;
	philo->last_ate = 0;
	philo->left_fork = 0;
	philo->right_fork = &(philo->next->left_fork);
	philo->left_mutex = dinner->mutex_fork[id - 1];
	philo->right_mutex = &(philo->next->left_mutex);
	philo->main = dinner;
	philo->next = NULL;
}

void	philo_list(t_philo **philos, t_main *dinner)
{
	int		id;
	t_philo	*philo;
	t_philo	*temp;

	id = 0;
	while (++id <= dinner->amt_of_philo)
	{
		philo = malloc(sizeof(t_philo));
		init_philo(dinner, philo, id);
		if (!*philos)
			*philos = philo;
		else
		{
			temp = *philos;
			while (temp->next != NULL)
				temp = temp->next;
			if (id == dinner->amt_of_philo && id != 1)
			{
				temp->next = philo;
				philo->next = *philos;
				return ;
			}
			temp->next = philo;
		}
	}
}
