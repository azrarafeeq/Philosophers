/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:40:03 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/05 18:07:27 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initial_parse(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr("\033[0;31mError : Invalid number of arguments\n\033[0m");
		return (1);
	}
	if (not_digit(argc, argv) || ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 60
		|| ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
	{
		ft_putstr("\033[0;31mError : Invalid argument\n\033[0m");
		return (1);
	}
	if (ft_atoi(argv[1]) > 200)
	{
		ft_putstr("\033[0;31mError : Philosophers more than 200\n\033[0m");
		return (1);
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
		{
			ft_putstr("\033[0;31mError : Philosophers can't eat\n\033[0m");
			return (1);
		}
	}
	return (0);
}

void	print_message(t_ph *ph, int flag, char *str)
{
	unsigned int	time;

	time = get_current_time() - ph->m->routine_start;
	pthread_mutex_lock(&(ph->m->finish_mutex));
	if (ph->m->routine_end != 1)
	{
		pthread_mutex_unlock(&(ph->m->finish_mutex));
		ft_putstr(RESET);
		if (flag == 1)
			ft_putstr(BLUE);
		else if (flag == 2)
			ft_putstr(GREEN);
		else if (flag == 3)
			ft_putstr(YELLOW);
		ft_putnbr(time);
		ft_putstr(" philo ");
		ft_putnbr(ph->id);
		ft_putstr(str);
	}
	else
		pthread_mutex_unlock(&(ph->m->finish_mutex));
}

void	print_death(t_m **din, int i, unsigned int time)
{
	pthread_mutex_lock(&((*din)->finish_mutex));
	(*din)->routine_end = 1;
	pthread_mutex_unlock(&((*din)->finish_mutex));
	pthread_mutex_lock(&((*din)->print_mutex));
	printf(RED);
	printf("%u philo %i died\033[0m\n", time, (*din)->m_p[i].id);
	pthread_mutex_unlock(&(*din)->print_mutex);
}

void	millie_sleep(unsigned int routine_time, t_ph *ph)
{
	unsigned int	current_time;
	int				i;

	current_time = get_current_time();
	pthread_mutex_lock(&(ph->m->finish_mutex));
	i = ph->m->routine_end;
	pthread_mutex_unlock(&(ph->m->finish_mutex));
	while (i == 0)
	{
		if (get_current_time() >= (routine_time + current_time))
			return ;
		usleep(250);
	}
}

int	main(int argc, char **argv)
{
	t_m	dinner;

	if (initial_parse(argc, argv))
		return (1);
	init_dinner(&dinner, argc, argv);
	init_ph(&dinner);
	ph_thread_create(&dinner);
	main_checker(&dinner, argc);
	return (0);
}
