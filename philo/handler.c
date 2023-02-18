/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:58:29 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/12 13:47:28 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, t_fork *min_fork, t_fork *max_fork)
{
	pthread_mutex_lock(&philo->data->death_check);
	if (philo->data->was_death || philo->data->everyone_eaten)
	{
		pthread_mutex_unlock(&philo->data->death_check);
		pthread_mutex_unlock(&min_fork->mutex);
		pthread_mutex_unlock(&max_fork->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_check);
	return (0);
}

int	eat(t_philo *philo)
{
	t_fork	*min_fork;
	t_fork	*max_fork;

	min_fork = philo->left;
	max_fork = philo->right;
	if (lock_fork(philo, min_fork) != 0)
		return (pthread_mutex_unlock(&min_fork->mutex));
	print(philo, FORK);
	if (lock_fork(philo, max_fork) != 0)
		return (pthread_mutex_unlock(&min_fork->mutex));
	if (check_death(philo, min_fork, max_fork))
		return (1);
	print(philo, FORK);
	print(philo, EAT);
	pthread_mutex_lock(&philo->condition_update);
	philo->dinners_count++;
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->condition_update);
	sl(philo->data->time_to_eat);
	pthread_mutex_unlock(&min_fork->mutex);
	pthread_mutex_unlock(&max_fork->mutex);
	return (0);
}

int	check_philo(t_data *data, int *count, int i)
{
	long long	gap;

	pthread_mutex_lock(&data->philos[i].condition_update);
	gap = get_time() - data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->philos[i].condition_update);
	if (gap > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_check);
		data->was_death = 1;
		pthread_mutex_unlock(&data->death_check);
		print(&data->philos[i], DIED);
		return (1);
	}
	pthread_mutex_lock(&data->philos[i].condition_update);
	if (data->philos[i].dinners_count >= data->dinners_count)
		(*count)++;
	pthread_mutex_unlock(&data->philos[i].condition_update);
	return (0);
}

void	death_cycle(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	while (!data->was_death)
	{
		i = 0;
		count = 0;
		while (i < data->philos_count)
		{
			if (check_philo(data, &count, i))
				break ;
			i++;
		}
		if (count >= data->philos_count)
		{
			pthread_mutex_lock(&data->death_check);
			data->everyone_eaten = 1;
			pthread_mutex_unlock(&data->death_check);
			break ;
		}
	}
}

void	*simulate(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2)
		usleep(2000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_check);
		if (philo->data->was_death || philo->data->everyone_eaten)
		{
			pthread_mutex_unlock(&philo->data->death_check);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_check);
		if (eat(philo))
			break ;
		print(philo, SLEEP);
		sl(philo->data->time_to_sleep);
		print(philo, THINK);
	}
	return (NULL);
}
