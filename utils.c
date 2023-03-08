/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:54:38 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/07 15:48:44 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	not_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argc != 1)
	{
		while (argv[i][j])
		{
			if (argv[i][j] <= '0' || argv[i][j] >= '9')
				return (1);
			j++;
		}
		j = 0;
		i++;
		argc--;
	}
	return (0);
}

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

void	ft_putnbr(int n)
{
	if (n == 2147483647)
	{
		write(1, "2147483647", 10);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = n * -1;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + 48);
}
