/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiara_ciapetti <chiara_ciapetti@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:15:29 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/22 13:17:53 by chiara_ciap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, struct timeval tv, char *message)
{
	long long int	millisec;

	gettimeofday(&tv, NULL);
	millisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo->t0;
	pthread_mutex_lock(&philo->mutex_is_dead);
	if (philo->is_dead == 0)
		printf("%lld %d %s\n", millisec, philo->id, message);
	pthread_mutex_unlock(&philo->mutex_is_dead);
}

void	ft_lock_fork(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, tv, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, tv, "has taken a fork");
	print_message(philo, tv, "is eating");
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->time_last_meal = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_unlock(&philo->mutex_last_meal);
	my_usleep(philo->input->time_to_eat * 1000);
}

void	ft_lock_fork_first(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, tv, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, tv, "has taken a fork");
	print_message(philo, tv, "is eating");
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->time_last_meal = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	pthread_mutex_unlock(&philo->mutex_last_meal);
	my_usleep(philo->input->time_to_eat * 1000);
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
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
