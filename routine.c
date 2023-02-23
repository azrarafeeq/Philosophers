/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:04:38 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/23 19:21:36 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	useconds_t	think_time;

	pthread_mutex_lock(&(philo->main->print_mutex));
	think_time = get_current_time() - philo->main->routine_start;
	print_message(think_time, philo->id, 1);
	pthread_mutex_unlock(&(philo->main->print_mutex));
}

void	eating(t_philo *philo)
{
	useconds_t	eat_time;

	thinking(philo);
	pthread_mutex_lock(&(philo->left_mutex));
	philo->left_fork = 1;
		printf("HELLO\n");
	printf("the left fork of philo %i\n", *(philo->right_fork));
	printf("the id of philo %i\n", philo->id);
	if (*(philo->right_fork) == 1)
	{
		philo->left_fork = 0;
		pthread_mutex_unlock(&(philo->left_mutex));
	}
	else
	{
		*(philo->right_fork) = 1;
		pthread_mutex_lock(&(philo->main->print_mutex));
		eat_time = get_current_time() - philo->main->routine_start;
		print_message(eat_time, philo->id, 4);
		print_message(eat_time, philo->id, 5);
		print_message(eat_time, philo->id, 2);
		pthread_mutex_unlock(&(philo->main->print_mutex));
		millie_sleep(philo->main->time_to_eat);
		pthread_mutex_unlock(&(philo->left_mutex));
	}

}

/* void	sleeping(t_philo *philo)
{

} */
