/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:01:07 by amitcul           #+#    #+#             */
/*   Updated: 2023/01/29 13:24:19 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
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
	t_timeval	tv;
	int			time;

	gettimeofday(&tv, 0);
	time = (tv.tv_sec - philo->program_start_time.tv_sec) * 1000
			+ (tv.tv_usec - philo->program_start_time.tv_usec) / 1000;
	printf("%d %d %s\n", time, philo->philo, message);
}

void	update_last_eating_time(t_timeval *last_time_eat, t_philo *philo,
								int was_sleeping)
{
	(void)last_time_eat;
	(void)philo;
	(void)was_sleeping;
}
