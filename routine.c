/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:04:38 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/26 18:40:52 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_available(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_mutex));
	pthread_mutex_lock(&(philo->left_mutex));
	if (philo->main->amt_of_philo != 1)
	{
		if (philo->main->forks[philo->right_fork] == 0
			&& philo->main->forks[philo->left_fork] == 0)
		{
			philo->main->forks[philo->right_fork] = 1;
			philo->main->forks[philo->left_fork] = 1;
			pthread_mutex_unlock(&(philo->right_mutex));
			pthread_mutex_unlock(&(philo->left_mutex));
			return (1);
		}
	}
	pthread_mutex_unlock(&(philo->right_mutex));
	pthread_mutex_unlock(&(philo->left_mutex));
	return (0);
}

int	eating(t_philo *philo)
{
	philo->eat_start = get_current_time() - philo->main->routine_start;
	if (philo->eat_start - philo->last_ate >= philo->main->time_to_die)
	{
		pthread_mutex_lock(&(philo->main->finish_mutex));
		philo->main->routine_end = 1;
		pthread_mutex_unlock(&(philo->main->finish_mutex));
		pthread_mutex_lock(&(philo->main->print_mutex));
		printf(RED);
		printf("%u philo %i died\n", philo->eat_start, philo->id);
		printf(RESET);
		pthread_mutex_unlock(&(philo->main->print_mutex));
		return (1);
	}
	pthread_mutex_lock(&(philo->main->print_mutex));
	printf("%u philo %i has taken right fork\n", philo->eat_start, philo->id);
	printf("%u philo %i has taken left fork\n", philo->eat_start, philo->id);
	printf(GREEN);
	printf("%u philo %i is eating\n", philo->eat_start, philo->id);
	printf(RESET);
	pthread_mutex_unlock(&(philo->main->print_mutex));
	millie_sleep(philo->main->time_to_eat, philo);
	philo->times_eaten++;
	philo->last_ate = get_current_time() - philo->main->routine_start;
	pthread_mutex_lock(&(philo->right_mutex));
	pthread_mutex_lock(&(philo->left_mutex));
	philo->main->forks[philo->right_fork] = 0;
	philo->main->forks[philo->left_fork] = 0;
	pthread_mutex_unlock(&(philo->right_mutex));
	pthread_mutex_unlock(&(philo->left_mutex));
	return (0);
}

void	sleeping(t_philo *philo)
{
	useconds_t	sleep_time;

	pthread_mutex_lock(&(philo->main->time_mutex));
	sleep_time = get_current_time() - philo->main->routine_start;
	pthread_mutex_unlock(&(philo->main->time_mutex));
	pthread_mutex_lock(&(philo->main->print_mutex));
	printf(YELLOW);
	printf("%u philo %i is sleeping\n", sleep_time, philo->id);
	printf(RESET);
	pthread_mutex_unlock(&(philo->main->print_mutex));
	millie_sleep(philo->main->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	useconds_t	think_time;

	pthread_mutex_lock(&(philo->main->time_mutex));
	think_time = get_current_time() - philo->main->routine_start;
	pthread_mutex_unlock(&(philo->main->time_mutex));
	pthread_mutex_lock(&(philo->main->print_mutex));
	printf(BLUE);
	printf("%u philo %i is thinking\n", think_time, philo->id);
	printf(RESET);
	pthread_mutex_unlock(&(philo->main->print_mutex));
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (1 && philo->main->routine_end != 1 && philo->main->amt_to_eat != 0)
	{
		if (forks_available(philo) && philo->main->routine_end != 1)
		{
			if (eating(philo))
				return (NULL);
			if (philo->main->routine_end != 1)
				sleeping(philo);
			if (philo->main->routine_end != 1)
				thinking(philo);
		}
		usleep(100);
	}
	return (NULL);
}
