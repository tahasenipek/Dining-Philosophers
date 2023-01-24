/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philofill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenipek <msenipek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:59:31 by msenipek          #+#    #+#             */
/*   Updated: 2022/10/19 12:51:00 by msenipek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutexassigment(t_philo *philo, pthread_mutex_t *fork, int len)
{
	int	i;

	i = 0;
	if (len == 1)
	{
		philo[0].l_frk = &fork[0];
	}
	else
	{
		while (i < len)
		{
			philo[i].l_frk = &fork[i];
			philo[i].r_frk = &fork[(i + 1) % len];
			i++;
		}
	}
	philo->fork = fork;
}

void	philo_quality(t_philo *philo, char **av)
{
	int	len;
	int	i;

	i = 0;
	len = ft_atoi(av[1]);
	while (i < len)
	{
		philo[i].id = i + 1;
		philo[i].count_philo = len;
		philo[i].time_die = ft_atoi(av[2]);
		philo[i].time_eat = ft_atoi(av[3]);
		philo[i].time_sleep = ft_atoi(av[4]);
		philo[i].diededtime = ft_atoi(av[2]);
		philo[i].must_eater = -1;
		if (av[5])
			philo[i].must_eater = ft_atoi(av[5]);
		i++;
	}
}

void	philo_filling(t_philo *philo, int len, char **av)
{
	pthread_mutex_t	*lock;
	int				i;
	int				*dead;
	int				*full;

	i = 0;
	lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(lock, NULL);
	dead = malloc (sizeof(int));
	full = malloc(sizeof(int));
	*dead = 0;
	*full = 0;
	philo_quality(philo, av);
	while (i < len)
	{
		philo[i].s_time = 0;
		philo[i].mil_sn = 0;
		philo[i].lock = lock;
		philo[i].full = full;
		philo[i].ph_dead = dead;
		philo[i].start_eattime = 0;
		philo[i].hm_eat = 0;
		i++;
	}
}

void	deadedcheck(t_philo *philo)
{
	while (1 && philo->count_philo != 1)
	{
		pthread_mutex_lock(philo->lock);
		if (*philo->ph_dead == 1)
		{
			return ;
		}
		pthread_mutex_unlock(philo->lock);
	}
}

void	thread_all(t_philo *philo, int philo_size)
{
	int	i;

	i = 0;
	if (philo_size == 1)
		senderone(philo, philo_size);
	else
	{
		i = 0;
		while (i < philo_size)
		{
			pthread_create(&philo[i].thread, NULL, (void *)looping, &philo[i]);
			pthread_detach(philo[i].thread);
			i += 2;
		}
		i = 1;
		while (i < philo_size)
		{
			pthread_create(&philo[i].thread, NULL, (void *)looping, &philo[i]);
			pthread_detach(philo[i].thread);
			i += 2;
		}
	}
}
