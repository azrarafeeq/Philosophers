/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:40:03 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/26 18:58:12 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initial_parse(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Number of arguments not equal to 5 or 6\n");
		return (1);
	}
	else if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (1);
	return (0);
}

void	philo_thread_create(t_main *dinner)
{
	int		i;

	i = 0;
	while (i < dinner->amt_of_philo)
	{
		pthread_create(&(dinner->philos[i].philo),
			NULL, &routine, &(dinner->philos[i]));
		usleep(200);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_main	*dinner;
	int		j;

	dinner = malloc(sizeof(t_main));
	if (initial_parse(argc, argv))
		return (1);
	init_dinner(dinner, argc, argv);
	init_philo(dinner);
	philo_thread_create(dinner);
	printf("DOES IT COME BACK IN THE MAIN\n");
	checker(dinner, argc);
	j = 0;
	while (j < dinner->amt_of_philo)
	{
		pthread_join(dinner->philos[j].philo, NULL);
		j++;
	}
	free(dinner);
}

//1. have to put conditions for one philo
//2. have to put condition for the amount of time a philo can eat - for 0 also
//3. have to check how to communicate between routine while loop and 
// checker while loop if a philo died or nbr to eat is reached

//two philos cannot communicate with each other but the main can communicate
//with other philosophers