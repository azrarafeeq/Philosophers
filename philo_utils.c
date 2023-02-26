/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:28:01 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/25 22:04:59 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ws_and_sign_check(const char *str, int *i, int *ve)
{
	while (str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\v'
		|| str[*i] == '\f' || str[*i] == '\r' || str[*i] == ' ')
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*ve = -1;
		(*i)++;
	}
	return ;
}

int	ft_atoi(const char *str)
{
	int				i;
	int				ve;
	unsigned long	num;

	i = 0;
	ve = 1;
	num = 0;
	ws_and_sign_check(str, &i, &ve);
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
		if (num > 2147483647 && ve == 1)
			return (-1);
		if (num > 2147483648 && ve == -1)
			return (-1);
	}
	return (num * ve);
}

useconds_t	get_current_time(void)
{
	useconds_t		millie_seconds;
	struct timeval	time;

	gettimeofday(&time, NULL);
	millie_seconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (millie_seconds);
}

void	millie_sleep(useconds_t routine_time, t_philo *philo)
{
	philo->current_time = get_current_time();
	while (get_current_time() < (routine_time + philo->current_time))
		usleep(50);
}
