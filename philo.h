/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenipek <msenipek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:38:47 by msenipek          #+#    #+#             */
/*   Updated: 2022/10/19 12:42:28 by msenipek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	int				count_philo;
	int				id;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			last_eattime;
	long			start_eattime;
	long			diededtime;
	int				hm_eat;
	int				must_eater;
	int				check_eat;
	int				start_time;
	int				*full;
	int				*ph_dead;
	long			s_time;
	long			mil_sn;
	struct timeval	tv;
	struct s_philo	*all;
	pthread_t		thread;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*l_frk;
	pthread_mutex_t	*r_frk;
}			t_philo;

//|||||||||||| philo.c with main ||||||||||

pthread_mutex_t	*mutex_initializer(int len);
int				ft_atoi(char *s);
int				checker(char **av);
int				checkercount(int ac, char **av);

//||||||||||||||| philofill.c|||||||||||||

void			philo_filling(t_philo *philo, int len, char **av);
void			mutexassigment(t_philo *philo, pthread_mutex_t *fork, int len);
void			philo_quality(t_philo *philo, char **av);
void			thread_all(t_philo *philo, int philo_size);
void			deadedcheck(t_philo *philo);

//||||||||||||||| looping.c|||||||||||||||

void			getintime(t_philo *philo);
void			*looping(t_philo *philo);
void			allfree(t_philo *philo);
void			philo_killer(t_philo *philo);
void			deadedcheck(t_philo *philo);
int				ft_usleep(t_philo *philo, int die_time);

//|||||||||||||||| looper.c ||||||||||||||

void			takingforks(t_philo *philo);
void			sleeping(t_philo *philo);
void			eating(t_philo *philo);
void			thinking(t_philo *philo);

//|||||||||||||| ex.c |||||||||||||||||||

void			senderone(t_philo *philo, int philo_size);
void			sendertwo(t_philo *philo);

#endif