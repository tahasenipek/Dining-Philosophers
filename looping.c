/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenipek <msenipek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:04:09 by msenipek          #+#    #+#             */
/*   Updated: 2022/10/19 14:58:16 by msenipek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	getintime(t_philo *philo)
{
	gettimeofday(&philo->tv, NULL);
	philo->mil_sn = (philo->tv.tv_sec * 1000) + (philo->tv.tv_usec / 1000);
	if (philo->s_time == 0)
		philo->s_time = philo->mil_sn;
	philo->start_time = philo->mil_sn - philo->s_time;
}

void	philo_killer(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (!*philo->ph_dead)
	{
		printf("%d %d is died\n", philo->start_time, philo->id);
		*philo->ph_dead = 1;
	}
	pthread_mutex_unlock(philo->lock);
}

void	allfree(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->count_philo)
		pthread_mutex_destroy(&philo->fork[i++]);
	free(philo->fork);
	free(philo->lock);
	free(philo->ph_dead);
	free(philo->full);
	free(philo);
}

int	ft_usleep(t_philo *philo, int die_time)
{
	long	time;

	getintime(philo);
	time = philo->start_time;
	while (philo->start_time < die_time + time)
	{
		getintime(philo);
		if (philo->start_time > philo->diededtime)
		{
			philo_killer(philo);
			return (0);
		}
		usleep(100);
	}
	return (1);
}

void	*looping(t_philo *philo)
{
	if (philo->count_philo == 1)
	{
		sendertwo(philo);
		return (NULL);
	}
	else
	{
		while (1)
		{
			takingforks(philo);
			eating(philo);
			if (philo->hm_eat == philo->must_eater)
				break ;
			sleeping(philo);
			thinking(philo);
		}
	}
	*philo->full += 1;
	pthread_mutex_lock(philo->lock);
	if (*philo->full == philo->count_philo)
		*philo->ph_dead = 1;
	pthread_mutex_unlock(philo->lock);
	return (NULL);
}
