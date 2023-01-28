/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:37:19 by amitcul           #+#    #+#             */
/*   Updated: 2023/01/28 18:09:38 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_PHILOS 300

typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	int		fork;
	int		is_busy;
	t_mutex	mutex;
}	t_fork;

typedef struct s_util
{
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eating_times;
	struct timeval	start_time;
	t_mutex			stdout_mutex;
}	t_util;

/** utils **/
int	ft_atoi(char *str);

#endif
