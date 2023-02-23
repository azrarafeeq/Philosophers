/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:28:01 by arafeeq           #+#    #+#             */
/*   Updated: 2023/02/23 15:47:35 by arafeeq          ###   ########.fr       */
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

int	number_length(int n)
{
	int	intlen;

	intlen = 1;
	n = n / 10;
	while (n)
	{
		n = n / 10;
		intlen++;
	}
	return (intlen);
}

char	*number_conversion(int num, char *str, int len)
{
	while (num)
	{
		str[--len] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char				*str;
	int					len;
	unsigned int		num;

	num = n;
	len = number_length(n);
	if (n < 0)
	{
		len++;
		num = n * -1;
	}
	str = (char *)malloc (sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	str[--len] = (num % 10) + '0';
	num = num / 10;
	number_conversion(num, str, len);
	if (n < 0)
		str[0] = '-';
	return (str);
}
