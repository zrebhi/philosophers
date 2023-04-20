/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:12:58 by bgresse           #+#    #+#             */
/*   Updated: 2023/04/20 19:23:54 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "utils.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philosophers	t_philosophers;

typedef struct s_rules
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				optional_param;
	int				number_of_times_each_philosopher_must_eat;
}		t_rules;

typedef struct s_philo
{
	t_rules			rules;
	t_philosophers	*philos;
	unsigned long	start_time;
	int				dead_philo;
	int				full_bellies;
	int				*forksint;
	pthread_mutex_t	*forks;
	pthread_mutex_t	belly;
	pthread_mutex_t	stopper;
	pthread_mutex_t	writing;
}					t_philo;

struct s_philosophers
{
	pthread_t		thread_id;
	int				number;
	int				first_fork;
	int				second_fork;
	int				last_meal_time;
	int				meals_number;
	t_rules			rules;
	t_philo			*data;
};

/* Initialization */

void	ft_params_init(t_philo *data, int argc, char **argv);
int		ft_philos_init(t_philo *data);
int		ft_mutex_init(t_philo *data);

/* Philos */

int		ft_eat(t_philosophers *philo);
int		ft_sleep(unsigned long duration, t_philo *data);
int		ft_print_event(char *event, t_philosophers *philo, int dead);
int		ft_forktaker(t_philosophers *philo);
int		ft_forkchecker(t_philosophers *philo);
void	ft_swapforks(t_philosophers *philo);
void	ft_showstopper(t_philo *data);
int		ft_mutexer(t_philosophers	*philo, pthread_mutex_t *mutex);

#endif