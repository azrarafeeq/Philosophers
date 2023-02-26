/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:08:01 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/26 18:40:18 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_times_eaten(t_main *dinner)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= dinner->amt_of_philo)
	{
		if (dinner->philos[i].times_eaten == dinner->amt_to_eat)
			j++;
		i++;
	}
	if (j == dinner->amt_of_philo)
		return (1);
	return (0);
}

void	checker(t_main *dinner, int argc)
{
	int	i;

	i = -1;
	while (1)
	{
		if (argc == 6)
		{
			if (philo_times_eaten(dinner))
			{
				while (++i < dinner->amt_of_philo)
					pthread_detach(dinner->philos[i].philo);
				return ;
			}
		}
		if (dinner->routine_end == 1)
		{
			while (++i < dinner->amt_of_philo)
				pthread_detach(dinner->philos[i].philo);
			return ;
		}
		if (dinner->amt_of_philo == 1)
		{
			if (get_current_time() - dinner->routine_start
				>= dinner->time_to_die)
			{
				printf(RED);
				printf("%u philo 1 died\n", get_current_time() - dinner->routine_start);
				printf(RESET);
				pthread_detach(dinner->philos[0].philo);
				return ;
			}
		}
		if (dinner->amt_to_eat == 0)
		{
			while (++i < dinner->amt_of_philo)
				pthread_detach(dinner->philos[i].philo);
			return ;
		}
	}
}
