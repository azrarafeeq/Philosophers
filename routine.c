/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:04:38 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/08 13:39:58 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_available(t_ph *ph)
{
	pthread_mutex_lock(&(ph->m->mutex[ph->right_fork]));
	if (ph->m->forks[ph->right_fork] == 0)
	{
		pthread_mutex_unlock(&(ph->m->mutex[ph->right_fork]));
		pthread_mutex_lock(&(ph->m->mutex[ph->left_fork]));
		if (ph->m->forks[ph->left_fork] == 0)
		{
			pthread_mutex_unlock(&(ph->m->mutex[ph->left_fork]));
			return (1);
		}
		else
			pthread_mutex_unlock(&(ph->m->mutex[ph->left_fork]));
	}
	else
		pthread_mutex_unlock(&(ph->m->mutex[ph->right_fork]));
	return (0);
}

int	not_signed(t_ph *ph)
{
	pthread_mutex_lock(&(ph->m->sm[ph->sr]));
	if (ph->m->sign[ph->sr] != ph->id)
	{
		pthread_mutex_unlock(&(ph->m->sm[ph->sr]));
		pthread_mutex_lock(&(ph->m->sm[ph->sl]));
		if (ph->m->sign[ph->sl] != ph->id)
		{
			pthread_mutex_unlock(&(ph->m->sm[ph->sl]));
			return (1);
		}
		else
			pthread_mutex_unlock(&(ph->m->sm[ph->sl]));
	}
	else
		pthread_mutex_unlock(&(ph->m->sm[ph->sr]));
	return (0);
}

void	eating(t_ph *ph)
{
	pthread_mutex_lock(&(ph->m->last_ate_mutex));
	ph->last_ate = get_current_time() - ph->m->routine_start;
	pthread_mutex_unlock(&(ph->m->last_ate_mutex));
	pthread_mutex_lock(&(ph->m->mutex[ph->right_fork]));
	ph->m->forks[ph->right_fork] = 1;
	pthread_mutex_unlock(&(ph->m->mutex[ph->right_fork]));
	pthread_mutex_lock(&(ph->m->mutex[ph->left_fork]));
	ph->m->forks[ph->left_fork] = 1;
	pthread_mutex_unlock(&(ph->m->mutex[ph->left_fork]));
	pthread_mutex_lock(&(ph->m->sm[ph->sr]));
	ph->m->sign[ph->sr] = ph->id;
	pthread_mutex_unlock(&(ph->m->sm[ph->sr]));
	pthread_mutex_lock(&(ph->m->sm[ph->sl]));
	ph->m->sign[ph->sl] = ph->id;
	pthread_mutex_unlock(&(ph->m->sm[ph->sl]));
	millie_sleep(ph->m->time_to_eat, ph);
	pthread_mutex_lock(&(ph->m->mutex[ph->right_fork]));
	ph->m->forks[ph->right_fork] = 0;
	pthread_mutex_unlock(&(ph->m->mutex[ph->right_fork]));
	pthread_mutex_lock(&(ph->m->mutex[ph->left_fork]));
	ph->m->forks[ph->left_fork] = 0;
	pthread_mutex_unlock(&(ph->m->mutex[ph->left_fork]));
}

void	sleeping(t_ph *ph)
{
	pthread_mutex_lock(&(ph->m->print_mutex));
	print_message(ph, 3, " is sleeping\033[0m\n");
	pthread_mutex_unlock(&(ph->m->print_mutex));
	millie_sleep(ph->m->time_to_sleep, ph);
	pthread_mutex_lock(&(ph->m->print_mutex));
	print_message(ph, 1, " is thinking\033[0m\n");
	pthread_mutex_unlock(&(ph->m->print_mutex));
}

void	*routine(void *arg)
{
	t_ph			*ph;

	ph = (t_ph *)arg;
	while (1)
	{
		pthread_mutex_lock(&(ph->m->finish_mutex));
		if (ph->m->routine_end == 1)
		{
			pthread_mutex_unlock(&(ph->m->finish_mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(ph->m->finish_mutex));
		if (ph->m->amt_of_ph > 1 && forks_available(ph) && not_signed(ph))
		{
			pthread_mutex_lock(&(ph->m->print_mutex));
			print_message(ph, 0, " has taken the right fork\033[0m\n");
			print_message(ph, 0, " has taken the left fork\033[0m\n");
			print_message(ph, 2, " is eating\033[0m\n");
			pthread_mutex_unlock(&(ph->m->print_mutex));
			eating(ph);
			pthread_mutex_lock(&(ph->m->times_eaten_mutex));
			ph->times_eaten++;
			pthread_mutex_unlock(&(ph->m->times_eaten_mutex));
			sleeping(ph);
		}
	}
}
