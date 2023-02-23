/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:46:27 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/23 18:24:50 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

useconds_t	get_current_time(void)
{
	useconds_t		millie_seconds;
	struct timeval	time;

	gettimeofday(&time, NULL);
	millie_seconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (millie_seconds);
}

void	millie_sleep(useconds_t routine_time)
{
	useconds_t		current_time;

	current_time = get_current_time();
	while (get_current_time() < (routine_time + current_time))
		usleep(100);
}

void	print_message(useconds_t time, int id, int flag)
{
	write(1, ft_itoa(time), ft_strlen(ft_itoa(time)));
	if (flag == 1)
		ft_putstr(" \033[0;34m philo ");
	else if (flag == 2)
		ft_putstr("\033[0;32m mphilo ");
	else if (flag == 3)
		ft_putstr("\033[0;33m mphilo ");
	else
		ft_putstr("mphilo ");
	ft_putstr(ft_itoa(id));
	if (flag == 1)
		ft_putstr(" is thinking\033[0m\n");
	else if (flag == 2)
		ft_putstr(" is eating\033[0m\n");
	else if (flag == 3)
		ft_putstr(" is sleeping\033[0m\n");
	else if (flag == 4)
		ft_putstr(" has taken right fork\n");
	else if (flag == 5)
		ft_putstr(" has taken left fork\n");
}

