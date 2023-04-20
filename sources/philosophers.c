/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:57:27 by zrebhi            #+#    #+#             */
/*   Updated: 2023/04/05 17:46:27 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_mutexer(t_philosophers	*philo, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	pthread_mutex_lock(&philo->data->stopper);
	if (philo->data->dead_philo || philo->data->full_bellies)
		return (pthread_mutex_unlock(&philo->data->stopper), \
		pthread_mutex_unlock(mutex), 1);
	pthread_mutex_unlock(&philo->data->stopper);
	return (0);
}

int	ft_print_event(char *event, t_philosophers *philo, int dead_philo)
{
	int	time;

	if (ft_mutexer(philo, &philo->data->writing))
	{
		time = get_time() - philo->data->start_time;
		if (dead_philo)
			printf("%d %d %s\n", time, philo->number, event);
		return (1);
	}
	time = get_time() - philo->data->start_time;
	printf("%d %d %s\n", time, philo->number, event);
	pthread_mutex_unlock(&philo->data->writing);
	return (0);
}

int	ft_eat(t_philosophers *philo)
{
	if (ft_print_event("is eating", philo, 0))
		return (1);
	pthread_mutex_lock(&philo->data->stopper);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->stopper);
	if (ft_sleep(philo->data->rules.time_to_eat, philo->data))
		return (1);
	if (ft_mutexer(philo, &philo->data->forks[philo->first_fork]))
		return (1);
	philo->data->forksint[philo->first_fork] = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
	if (ft_mutexer(philo, &philo->data->forks[philo->second_fork]))
		return (1);
	philo->data->forksint[philo->second_fork] = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
	if (ft_mutexer(philo, &philo->data->belly))
		return (1);
	philo->meals_number++;
	pthread_mutex_unlock(&philo->data->belly);
	return (0);
}

int	ft_sleep(unsigned long duration, t_philo *data)
{
	unsigned long	start;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&data->stopper);
		if (data->full_bellies || data->dead_philo)
		{
			pthread_mutex_unlock(&data->stopper);
			break ;
		}
		pthread_mutex_unlock(&data->stopper);
		if (get_time() - start >= duration)
			return (0);
		usleep(10);
	}
	return (1);
}
