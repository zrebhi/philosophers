/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:36:15 by zrebhi            #+#    #+#             */
/*   Updated: 2023/04/20 19:21:31 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_firstfork(t_philosophers *philo)
{
	if (ft_mutexer(philo, &philo->data->forks[philo->first_fork]))
		return (1);
	if (philo->data->rules.number_of_philosophers > 1)
		if (ft_mutexer(philo, &philo->data->forks[philo->second_fork]))
			return (pthread_mutex_unlock \
			(&philo->data->forks[philo->first_fork]), 1);
	if (!philo->data->forksint[philo->first_fork])
	{
		philo->data->forksint[philo->first_fork] = philo->number;
		pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
		if (ft_print_event("has taken a fork", philo, 0))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
			return (1);
		}
	}
	else
		pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
	return (0);
}

int	ft_forktaker(t_philosophers *philo)
{
	if (ft_firstfork(philo))
		return (1);
	if (philo->data->rules.number_of_philosophers <= 1)
		return (1);
	if (!philo->data->forksint[philo->second_fork])
	{
		philo->data->forksint[philo->second_fork] = philo->number;
		pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
		if (ft_print_event("has taken a fork", philo, 0))
			return (1);
	}
	else
		pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
	return (0);
}

int	ft_forkchecker(t_philosophers *philo)
{
	if (philo->data->rules.number_of_philosophers <= 1)
		return (ft_forktaker(philo));
	while (1)
	{
		if (ft_forktaker(philo))
			return (1);
		if (ft_mutexer(philo, &philo->data->forks[philo->first_fork]))
			return (1);
		if (ft_mutexer(philo, &philo->data->forks[philo->second_fork]))
			return (pthread_mutex_unlock \
			(&philo->data->forks[philo->first_fork]), 1);
		if (philo->data->forksint[philo->first_fork] == philo->number && \
		philo->data->forksint[philo->second_fork] == philo->number)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
			pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
			break ;
		}
		pthread_mutex_unlock(&philo->data->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->second_fork]);
	}
	return (0);
}

void	ft_swapforks(t_philosophers *philo)
{
	int	swap;

	if (philo->number % 2)
	{
		swap = philo->first_fork;
		philo->first_fork = philo->second_fork;
		philo->second_fork = swap;
	}
}
