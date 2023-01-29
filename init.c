/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:50:24 by amitcul           #+#    #+#             */
/*   Updated: 2023/01/29 13:26:00 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo *philos, t_fork *forks, t_util *util)
{
	int			i;
	pthread_t	ptid;

	i = 0;
	while (i < util->philos_count)
	{
		philos[i].philo = i + 1;
		philos[i].left = forks + i;
		philos[i].right = forks + ((i + 1) % util->philos_count);
		philos[i].stdout_mutex = &(util->stdout_mutex);
		if (pthread_mutex_init(philos[i].condition_mutex, 0))
			return (1);
		philos[i].eating_times = 0;
		philos[i].time_to_eat = util->time_to_eat;
		philos[i].time_to_sleep = util->time_to_sleep;
		philos[i].program_start_time = util->start_time;
		gettimeofday(&philos[i].last_time_eat, 0);
		if (pthread_create(&ptid, 0, philo_func, &(philos[i])))
			return (1);
		pthread_detach(ptid);
		i++;
	}
	return (0);
}

int	init_forks(t_fork *forks, int forks_count)
{
	int	i;

	i = 0;
	while (i < forks_count)
	{
		forks[i].fork = i + 1;
		forks[i].is_busy = 0;
		if (pthread_mutex_init(&forks[i].mutex, 0))
			return (1);
		i++;
	}
	return (0);
}
