/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:36:58 by amitcul           #+#    #+#             */
/*   Updated: 2023/01/29 13:16:30 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//TODO: Add compile flags

/**
 * Read and parse input data
 *
 * t_util {
 * 		philos_count
 * 		time_to_die
 * 		time_to_eat
 * 		time_to_sleep
 * 		eating_times [ Optional ]
 * 		start_time - struct timeval, time when program was started
 * 		stdout_mutex - mutex to protect stdout
 * }
 *
 *
*/

static int	check_validation(t_util *util)
{
	if (util->eating_times == -1 || util->philos_count == -1
		|| util->time_to_die == -1 || util->time_to_eat == -1
		|| util->time_to_sleep == -1)
		return (1);
	return (0);
}

int	init_argc(t_util *util, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (argc == 5)
	{
		util->philos_count = ft_atoi(argv[1]);
		util->time_to_die = ft_atoi(argv[2]);
		util->time_to_eat = ft_atoi(argv[3]);
		util->time_to_sleep = ft_atoi(argv[4]);
	}
	else if (argc == 6)
		util->eating_times = ft_atoi(argv[5]);
	pthread_mutex_init(&util->stdout_mutex, 0);
	gettimeofday(&util->start_time, 0);
	return (check_validation(util));
}

int simulate(t_fork *forks, t_philo *philos, t_util *util)
{
	while (1)
	{
		util->curr_index = 0;
		util->eating_times = 1;//!
		while (util->curr_index < util->philos_count)
		{
			if (util->eating_times == -1
				|| philos[util->curr_index].eating_times < util->eating_times)
				util->eating_times = 0;
			if (philo_was_died(&philos[util->curr_index], util))
			{
				print(&philos[util->curr_index], DIED);
				forks_destroy(forks, util->philos_count);
				pthread_mutex_destroy(&util->stdout_mutex);
				return (0);
			}
		}
	}
	return (0);
}

/**
 * ./philo	number_of_philosophers time_to_die time_to_eat time_to_sleep
 * 			[number_of_times_each_philosopher_must_eat]
 * mandatory 4 arguments + 1 optional
*/

int	main(int argc, char **argv)
{
	t_fork	*forks;
	t_philo	*philos;
	t_util	util;

	forks = malloc(sizeof(t_fork) * MAX_PHILOS);
	if (!forks)
		return (1);
	philos = malloc(sizeof(t_philo) * MAX_PHILOS);
	if (!philos)
		return (1);
	if (init_argc(&util, argc, argv))
		return (1);
	if (init_forks(forks, util.philos_count))
		return (1);
	if (init_philos(philos, forks, &util))
		return (1);
	return (simulate(forks, philos, &util));
}
