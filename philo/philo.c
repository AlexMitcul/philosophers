/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:51:10 by amitcul           #+#    #+#             */
/*   Updated: 2023/01/29 14:21:40 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo, int was_sleeping)
{
	t_fork	*min_fork;
	t_fork	*max_fork;

	min_fork = philo->right;
	max_fork = philo->left;
	if (philo->left->fork < philo->right->fork)
	{
		min_fork = philo->left;
		max_fork = philo->right;
	}
	fork_lock(min_fork);
	print(philo, FORK);
	fork_lock(max_fork);
	print(philo, FORK);
	print(philo, EAT);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(philo->condition_mutex);
	philo->eating_times++;
	update_last_eating_time(&philo->last_time_eat, philo, was_sleeping);
	pthread_mutex_unlock(philo->condition_mutex);
	fork_unlock(max_fork);
	fork_unlock(min_fork);
}

void	philo_sleep(t_philo *philo)
{
	usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print(philo, THINK);
}

void	*philo_func(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo % 2 == 0)
		usleep(2500);
	philo_eat(philo, 0);
	philo_sleep(philo);
	philo_think(philo);
	while (1)
	{
		philo_eat(philo, 1);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (0);
}

int	philo_was_died(t_philo *philo, t_util *util)
{
	t_timeval	curr_time;

	gettimeofday(&curr_time, 0);
	pthread_mutex_lock(philo->condition_mutex);
	if ((curr_time.tv_sec - philo->last_time_eat.tv_sec) * 1000
		+ (curr_time.tv_usec - philo->last_time_eat.tv_usec + 500) / 1000
		>= util->time_to_die)
	{
		pthread_mutex_unlock(philo->condition_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->condition_mutex);
	return (0);
}
