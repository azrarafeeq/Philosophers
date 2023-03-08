/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:08:01 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/08 13:35:11 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_abs(unsigned int time, unsigned int last_ate)
{
	if (time <= last_ate)
		return (0);
	else
		return (time - last_ate);
}

int	ph_starvation(t_m *din)
{
	unsigned int	time;
	int				i;

	i = -1;
	while (++i < din->amt_of_ph)
	{
		time = get_current_time() - din->routine_start;
		pthread_mutex_lock(&(din->last_ate_mutex));
		if (ft_abs(time, din->m_p[i].last_ate) >= din->time_to_die)
		{
			pthread_mutex_unlock(&(din->last_ate_mutex));
			print_death(&din, i, time);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&din->last_ate_mutex);
		}
	}
	return (0);
}

int	ph_times_eaten(t_m *dinner)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < dinner->amt_of_ph)
	{
		pthread_mutex_lock(&(dinner->times_eaten_mutex));
		if (dinner->m_p[i].times_eaten == dinner->amt_to_eat)
		{
			pthread_mutex_unlock(&(dinner->times_eaten_mutex));
			j++;
		}
		else
			pthread_mutex_unlock(&(dinner->times_eaten_mutex));
	}
	if (j == dinner->amt_of_ph)
	{
		pthread_mutex_lock(&(dinner->finish_mutex));
		dinner->routine_end = 1;
		pthread_mutex_unlock(&(dinner->finish_mutex));
		return (1);
	}
	return (0);
}

void	join_and_destroy(t_m **dinner)
{
	int	i;

	i = -1;
	while (++i < (*dinner)->amt_of_ph)
		pthread_join((*dinner)->m_p[i].ph, NULL);
	i = -1;
	while (++i < (*dinner)->amt_of_ph)
		pthread_mutex_destroy(&((*dinner)->mutex[i]));
	i = -1;
	while (++i < (*dinner)->amt_of_ph)
		pthread_mutex_destroy(&((*dinner)->sm[i]));
	pthread_mutex_destroy(&((*dinner)->print_mutex));
	pthread_mutex_destroy(&((*dinner)->finish_mutex));
	pthread_mutex_destroy(&((*dinner)->times_eaten_mutex));
	pthread_mutex_destroy(&((*dinner)->last_ate_mutex));
	return ;
}

void	main_checker(t_m *dinner, int argc)
{
	while (1)
	{
		if (ph_starvation(dinner) == 1)
		{
			join_and_destroy(&dinner);
			return ;
		}
		if (argc == 6 && ph_times_eaten(dinner))
		{
			join_and_destroy(&dinner);
			return ;
		}
	}
}
