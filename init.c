/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:18:28 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/11 21:53:47 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philos_count);
	if (!data->philos)
		return (ERROR);
	i = 0;
	while (i < data->philos_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].dinners_count = 0;
		data->philos[i].data = data;
		data->philos[i].left = &data->forks[i];
		data->philos[i].right = &data->forks[(i + 1) % data->philos_count];
		if (data->philos[i].left->id > data->philos[i].right->id)
		{
			data->philos[i].left = &data->forks[(i + 1) % data->philos_count];
			data->philos[i].right = &data->forks[i];
		}
		pthread_mutex_init(&data->philos[i].condition_update, NULL);
		i++;
	}
	return (OK);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->philos_count);
	if (!data->forks)
		return (ERROR);
	i = 0;
	while (i < data->philos_count)
	{
		data->forks[i].id = i + 1;
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		i++;
	}
	return (OK);
}

int	validation(t_data *data)
{
	if (data->philos_count <= 0
		|| data->dinners_count <= 0
		|| data->time_to_die <= 0
		|| data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (1);
	return (0);
}

int	init(t_data *data, int argc, char **argv)
{
	if (!data || (argc != 5 && argc != 6))
		return (1);
	data->philos_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dinners_count = INT_MAX;
	data->was_death = 0;
	data->everyone_eaten = 0;
	pthread_mutex_init(&data->stdout, NULL);
	pthread_mutex_init(&data->death_check, NULL);
	if (argc == 6)
		data->dinners_count = ft_atoi(argv[5]);
	if (validation(data) || init_forks(data) || init_philos(data))
	{
		free(data);
		return (1);
	}
	return (0);
}
