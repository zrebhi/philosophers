/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:49:06 by zrebhi            #+#    #+#             */
/*   Updated: 2023/04/20 19:20:04 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_params_error(t_philo *data)
{
	if (data->rules.number_of_philosophers <= 0)
		return (ft_putstr_fd("There must be at least 1 philosopher.\n", 2), 1);
	if (data->rules.time_to_die < 0)
		return (ft_putstr_fd("Time to die must be a positive number.\n", 2), 2);
	if (data->rules.time_to_eat < 0)
		return (ft_putstr_fd("Time to eat must be a positive number.\n", 2), 3);
	if (data->rules.time_to_sleep < 0)
		return (ft_putstr_fd \
		("Time to sleep must be a positive number.\n", 2), 4);
	if (data->rules.optional_param && \
		data->rules.number_of_times_each_philosopher_must_eat < 0)
		return (ft_putstr_fd("Number of times each philosopher must \
		eat must be a positive number.\n", 2), 5);
	return (0);
}

void	ft_belly_checker(t_philo *data)
{
	int	i;

	i = 0;
	while (i < data->rules.number_of_philosophers)
	{
		if (ft_mutexer(&data->philos[i], &data->belly))
			return ;
		if (data->philos[i].meals_number < \
		data->rules.number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&data->belly);
			break ;
		}
		pthread_mutex_unlock(&data->belly);
		i++;
	}
	pthread_mutex_lock(&data->stopper);
	if (i == data->rules.number_of_philosophers)
		data->full_bellies = 1;
	pthread_mutex_unlock(&data->stopper);
}

void	ft_showstopper(t_philo *data)
{
	int	i;
	int	timer;

	while (!data->full_bellies)
	{
		i = -1;
		while (++i < data->rules.number_of_philosophers)
		{
			pthread_mutex_lock(&data->stopper);
			timer = (int)get_time() - data->philos[i].last_meal_time;
			if (timer > data->rules.time_to_die)
			{
				data->dead_philo = 1;
				pthread_mutex_unlock(&data->stopper);
				ft_print_event("died", &data->philos[i], 1);
				return ;
			}
			pthread_mutex_unlock(&data->stopper);
		}
		if (data->rules.optional_param)
			ft_belly_checker(data);
	}
}

int	ft_close_threads(t_philo *data)
{
	int	i;

	i = -1;
	while (++i < data->rules.number_of_philosophers)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (1);
	}
	i = -1;
	while (++i < data->rules.number_of_philosophers)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->belly);
	pthread_mutex_destroy(&data->stopper);
	pthread_mutex_destroy(&data->writing);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	data;

	if (argc < 5 || argc > 6)
		return (ft_putstr_fd("Invalid number of parameters.\n", 2), 1);
	ft_params_init(&data, argc, argv);
	if (ft_params_error(&data))
		return (1);
	if (ft_mutex_init(&data))
		return (2);
	if (ft_philos_init(&data))
		return (free(data.forks), free(data.forksint), 3);
	ft_showstopper(&data);
	if (ft_close_threads(&data))
		return (free(data.forks), free(data.forksint), free(data.philos), 4);
	free(data.forks);
	free(data.forksint);
	free(data.philos);
	return (0);
}
