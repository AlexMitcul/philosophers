/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:36:58 by amitcul           #+#    #+#             */
/*   Updated: 2023/01/28 18:09:20 by amitcul          ###   ########.fr       */
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

/**
 * ./philo	number_of_philosophers time_to_die time_to_eat time_to_sleep
 * 			[number_of_times_each_philosopher_must_eat]
 * mandatory 4 arguments + 1 optional
*/

int	main(int argc, char **argv)
{
	t_fork	forks[MAX_PHILOS];
	// t_phil	philos[MAX_PHILOS];
	t_util	util;

	if (init_argc(&util, argc, argv))
		return (1);
	// if (init_forks())
	// 	return (1);
	// if (init_philos())
	// 	return (1);
	// return (simulate());
}
