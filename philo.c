/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenipek <msenipek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:39:01 by msenipek          #+#    #+#             */
/*   Updated: 2022/10/19 19:53:53 by msenipek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*mutex_initializer(int len)
{
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	fork = malloc(sizeof(pthread_mutex_t) * len);
	if (!fork)
		return (0);
	while (i < len)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

int	checker(char **av)
{
	int	i;
	int	c;

	i = 1;
	while (av[i] && ft_atoi(av[i]) > 0)
	{	
		c = 0;
		while (av[i][c])
		{
			if (av[i][c] <= '9' && av[i][c] >= '0')
				c++;
			else
			{
				printf("Wrong argument\n");
				return (0);
			}
		}
		i++;
	}
	if (av[i] > 0)
	{
		printf("Error\nYou don't entered negative argument\n");
		return (0);
	}
	return (1);
}

int	checkercount(int ac, char **av)
{
	if (ac <= 6)
	{
		if (ac < 5)
		{
			printf("Error\nLess argument entered\n");
			return (0);
		}
		else
			if (checker(av) == 0)
				return (0);
	}
	else
	{
		printf("Error\nMore argument entered\n");
		return (0);
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int	res;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	res = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] <= '9' && s[i] >= '0')
	{
		res = (res * 10) + s[i] - '0';
		i++;
	}
	return (res * sign);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	int				len;

	if (checkercount(ac, av) == 0)
		return (0);
	len = ft_atoi(av[1]);
	philo = malloc(sizeof(t_philo) * len);
	philo->all = philo;
	fork = mutex_initializer(len);
	mutexassigment(philo, fork, len);
	philo_filling(philo, len, av);
	thread_all(philo, len);
	deadedcheck(philo);
	allfree(philo);
	return (0);
}
