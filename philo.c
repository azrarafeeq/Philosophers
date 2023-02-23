/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:40:03 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/23 19:34:11 by arafeeq          ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	eating(philo);
	//sleeping(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_main	dinner;
	t_philo	*philo;
	t_philo	*temp;

	philo = NULL;
	if (initial_parse(argc, argv))
		return (1);
	init_dinner(&dinner, argc, argv);
	philo_list(&philo, &dinner);
	temp = philo;
	/* printf("id of temp = %i\n", temp->id);
	printf("id of temp->next = %i\n", temp->next->id);
	printf("id of temp->next->next = %i\n", temp->next->next->id); */
	philo->main->routine_start = get_current_time();
	while (philo->next != temp)
	{
		printf("----------------------------------------------------\n");
		printf("ID of philo = %i\n", philo->id);
		printf("philo last_ate = %i\n", philo->last_ate);
		printf("philo left_fork = %i\n", philo->left_fork);
		printf("id of next philo = %i\n", philo->next->id);
		//printf("philo right_fork = %i\n", *(philo->right_fork));
		philo = philo->next;
	}
	printf("----------------------------------------------------\n");
	printf("ID of philo = %i\n", philo->id);
	printf("philo last_ate = %i\n", philo->last_ate);
	printf("philo left_fork = %i\n", philo->left_fork);
	printf("id of next philo = %i\n", philo->next->id);
	//printf("philo right_fork = %i\n", *(philo->right_fork));
	/* while (philo->next != temp && dinner.amt_of_philo != 1)
	{
		if (pthread_create(&(philo->philo), NULL, routine, philo) != 0)
			return (printf("Couldn't create thread %i\n", philo->id));
		usleep(200);
		philo = philo->next;
	}
	if (pthread_create(&(philo->philo), NULL, routine, philo) != 0)
		return (printf("Couldn't create thread %i\n", philo->id)); */
}
