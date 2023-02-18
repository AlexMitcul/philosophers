/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:17:43 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/12 13:47:49 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# include <limits.h>

# define FORK "has taken a fork"

# define EAT "is eating"

# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

# define ERROR 1
# define OK 0

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;

typedef struct s_fork
{
	int		id;
	t_mutex	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			*left;
	t_fork			*right;
	t_mutex			condition_update;
	int				dinners_count;
	long long		last_meal_time;
	pthread_t		thread_id;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int			philos_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			dinners_count;
	int			was_death;
	int			everyone_eaten;
	long long	start_time;
	t_mutex		stdout;
	t_mutex		death_check;
	t_fork		*forks;
	t_philo		*philos;
}	t_data;

int			ft_atoi(const char *str);
long long	get_time(void);
void		print(t_philo *philo, char *message);
int			lock_fork(t_philo *philo, t_fork *fork);
int			init(t_data *data, int argc, char **argv);
void		*simulate(void *data);
void		death_cycle(t_data *data);
void		sl(long long time);

#endif
