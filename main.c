/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:15:46 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/12 13:46:55 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->philos_count)
	{
		data->philos[i].last_meal_time = get_time();
		if (0 == pthread_create(&data->philos[i].thread_id, NULL,
				simulate, &data->philos[i]))
			pthread_detach(data->philos[i].thread_id);
		i++;
	}
	death_cycle(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (init(data, argc, argv))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	start_simulation(data);
	usleep(20000);
	free(data->philos);
	free(data->forks);
	free(data);
	return (0);
}
