/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenipek <msenipek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:37:03 by msenipek          #+#    #+#             */
/*   Updated: 2022/10/19 12:45:21 by msenipek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	takingforks(t_philo *philo)
{
	getintime(philo);
	pthread_mutex_lock(philo->l_frk);
	pthread_mutex_lock(philo->r_frk);
	getintime(philo);
	pthread_mutex_lock(philo->lock);
	if (*philo->ph_dead != 1)
	{
		printf("%d %d has taken a fork\n", philo->start_time, philo->id);
		printf("%d %d has taken a fork\n", philo->start_time, philo->id);
	}
	pthread_mutex_unlock(philo->lock);
}

void	eating(t_philo *philo)
{
	getintime(philo);
	pthread_mutex_lock(philo->lock);
	if (*philo->ph_dead == 0)
		printf("%d %d is eating\n", philo->start_time, philo->id);
	pthread_mutex_unlock(philo->lock);
	philo->diededtime = philo->start_time + philo->time_die;
	philo->hm_eat++;
	ft_usleep(philo, philo->time_eat);
	pthread_mutex_unlock(philo->l_frk);
	pthread_mutex_unlock(philo->r_frk);
}

void	sleeping(t_philo *philo)
{
	getintime(philo);
	pthread_mutex_lock(philo->lock);
	if (*philo->ph_dead == 0)
		printf("%d %d is sleeping\n", philo->start_time, philo->id);
	pthread_mutex_unlock(philo->lock);
	ft_usleep(philo, philo->time_eat);
}

void	thinking(t_philo *philo)
{
	getintime(philo);
	pthread_mutex_lock(philo->lock);
	if (*philo->ph_dead == 0)
		printf("%d %d is thinking\n", philo->start_time, philo->id);
	pthread_mutex_unlock(philo->lock);
}
