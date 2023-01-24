/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenipek <msenipek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:07:48 by msenipek          #+#    #+#             */
/*   Updated: 2022/10/19 13:11:57 by msenipek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	senderone(t_philo *philo, int philo_size)
{
	int	i;

	i = 0;
	if (philo_size == 1)
	{
		pthread_create(&philo[i].thread, NULL, (void *)looping, &philo[i]);
		pthread_join(philo[i].thread, NULL);
		pthread_detach(philo[i].thread);
	}
}

void	sendertwo(t_philo *philo)
{
	if (philo->count_philo == 1)
	{
		getintime(philo);
		printf("%d %d has taken a fork\n", philo->start_time, philo->id);
		*philo->ph_dead = 1;
		ft_usleep(philo, philo->time_die);
		printf ("%ld %d is died\n", philo->time_die, philo->id);
	}
}
