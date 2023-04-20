/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:07:07 by zrebhi            #+#    #+#             */
/*   Updated: 2023/04/20 20:00:53 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_delay(t_philosophers *philo)
{
	philo->data->start_time = get_time();
	if (philo->number % 2)
		ft_sleep(30, philo->data);
}

void	*routine(void *args)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)args;
	ft_delay(philo);
	while (1)
	{
		if (ft_print_event("is thinking", philo, 0))
			break ;
		pthread_mutex_lock(&philo->data->stopper);
		if (philo->data->full_bellies || philo->data->dead_philo)
		{
			pthread_mutex_unlock(&philo->data->stopper);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stopper);
		if (ft_forkchecker(philo))
			break ;
		if (ft_eat(philo))
			break ;
		if (ft_print_event("is sleeping", philo, 0))
			break ;
		if (ft_sleep(philo->data->rules.time_to_sleep, philo->data))
			break ;
	}
	return (NULL);
}

void	ft_params_init(t_philo *data, int argc, char **argv)
{
	data->rules.number_of_philosophers = ft_atoi(argv[1]);
	data->rules.time_to_die = ft_atoi(argv[2]);
	data->rules.time_to_eat = ft_atoi(argv[3]);
	data->rules.time_to_sleep = ft_atoi(argv[4]);
	data->rules.optional_param = 0;
	data->full_bellies = 0;
	data->dead_philo = 0;
	if (argc == 6)
	{
		data->rules.optional_param = 1;
		data->rules.number_of_times_each_philosopher_must_eat \
		= (int)ft_atoi(argv[5]);
	}
}

int	ft_philos_init(t_philo *data)
{
	int	i;

	data->philos = ft_calloc(sizeof(t_philosophers), \
	data->rules.number_of_philosophers);
	if (!data->philos)
		return (1);
	i = -1;
	while (++i < data->rules.number_of_philosophers)
	{
		data->philos[i].last_meal_time = get_time();
		data->philos[i].number = i + 1;
		data->philos[i].first_fork = i;
		data->philos[i].second_fork = \
		(i + 1) % data->rules.number_of_philosophers;
		ft_swapforks(&data->philos[i]);
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].rules = data->rules;
		data->philos[i].meals_number = 0;
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].thread_id, \
			NULL, routine, &data->philos[i]))
			return (free(data->philos), 1);
	}
	return (0);
}

int	ft_mutex_init(t_philo *data)
{
	int	i;

	data->forks = ft_calloc(sizeof(pthread_mutex_t), \
	data->rules.number_of_philosophers);
	if (!data->forks)
		return (1);
	data->forksint = ft_calloc(sizeof(int), \
	data->rules.number_of_philosophers);
	if (!data->forksint)
		return (free(data->forksint), 1);
	i = -1;
	while (++i < data->rules.number_of_philosophers)
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (free(data->forks), free(data->forksint), 1);
	if (pthread_mutex_init(&data->writing, NULL))
		return (free(data->forks), free(data->forksint), 1);
	if (pthread_mutex_init(&data->stopper, NULL))
		return (free(data->forks), free(data->forksint), 1);
	if (pthread_mutex_init(&data->belly, NULL))
		return (free(data->forks), free(data->forksint), 1);
	return (0);
}
