/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:15:29 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/04 16:21:56 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, struct timeval *tv, char *message)
{
	long long int	millisec;

	millisec = (tv->tv_sec * 1000) + (tv->tv_usec / 1000) - philo->t0;
	pthread_mutex_lock(philo->mutex_is_dead);
	if (philo->is_dead == 0)
		printf("%lld %d %s\n", millisec, philo->id, message);
	pthread_mutex_unlock(philo->mutex_is_dead);
}

void	ft_lock_fork(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(philo->right_fork);
	gettimeofday(&tv, NULL);
	print_message(philo, &tv, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	gettimeofday(&tv, NULL);
	print_message(philo, &tv, "has taken a fork");
	gettimeofday(&tv, NULL);
	print_message(philo, &tv, "is eating");
	pthread_mutex_lock(philo->mutex_last_meal);
	philo->time_last_meal = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_unlock(philo->mutex_last_meal);
	usleep(philo->input->time_to_eat * 1000);
}

void	ft_lock_fork_first(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(philo->left_fork);
	gettimeofday(&tv, NULL);
	print_message(philo, &tv, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	gettimeofday(&tv, NULL);
	print_message(philo, &tv, "has taken a fork");
	gettimeofday(&tv, NULL);
	print_message(philo, &tv, "is eating");
	pthread_mutex_lock(philo->mutex_last_meal);
	philo->time_last_meal = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	pthread_mutex_unlock(philo->mutex_last_meal);
	usleep(philo->input->time_to_eat * 1000);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_lock_fork(philo);
	else
		ft_lock_fork_first(philo);
}

void	ft_unlock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
