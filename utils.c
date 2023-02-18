/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:22:23 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/12 13:47:36 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0' || res <= 0)
		return (-1);
	return (res);
}

void	print(t_philo *philo, char *message)
{
	long long	time;
	long long	gap;

	time = get_time();
	gap = time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->stdout);
	printf("%lld %d %s\n", gap, philo->id, message);
	pthread_mutex_unlock(&philo->data->stdout);
}

void	sl(long long time)
{
	long long	start_time;
	long long	curr_time;

	curr_time = get_time();
	start_time = get_time();
	while (curr_time - start_time < time)
	{
		usleep(10);
		curr_time = get_time();
	}
}

int	lock_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&philo->data->death_check);
	if (philo->data->was_death || philo->data->everyone_eaten)
	{
		pthread_mutex_unlock(&philo->data->death_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_check);
	pthread_mutex_lock(&fork->mutex);
	return (0);
}
