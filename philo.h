/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:37:19 by amitcul           #+#    #+#             */
/*   Updated: 2023/01/29 13:26:00 by amitcul          ###   ########.fr       */
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

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef pthread_mutex_t t_mutex;
typedef struct timeval t_timeval;

typedef struct s_fork
{
	int		fork;
	int		is_busy;
	t_mutex	mutex;
}	t_fork;

typedef struct s_util
{
	int			curr_index;
	int			philos_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eating_times;
	t_timeval	start_time;
	t_mutex		stdout_mutex;
}	t_util;

typedef struct s_philo
{
	int			philo;
	t_fork		*left;
	t_fork		*right;
	t_mutex		*stdout_mutex;
	t_mutex		*condition_mutex;
	int			eating_times;
	t_timeval	last_time_eat;
	long int	time_to_eat;
	long int	time_to_sleep;
	t_timeval	program_start_time;
}	t_philo;

/** utils **/
int		ft_atoi(char *str);
void	print(t_philo *philo, char *message);
void	update_last_eating_time(t_timeval *last_time_eat, t_philo *philo,
			int was_sleeping);

/** philo **/
void	*philo_func(void *data);
int		philo_was_died(t_philo *philo, t_util *util);

/** forks **/
void	forks_destroy(t_fork *forks, int count);
void	fork_lock(t_fork *fork);
void	fork_unlock(t_fork *fork);

/** init **/
int		init_forks(t_fork *forks, int forks_count);
int		init_philos(t_philo *philos, t_fork *forks, t_util *util);

#endif
