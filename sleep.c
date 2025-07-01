/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:55:46 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/01 16:52:34 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	print_message(philo, tv, "is sleeping");
	my_usleep(philo->input->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	print_message(philo, tv, "is thinking");
	my_usleep(100);
}

void	my_usleep(int time_to_wait)
{
	struct timeval	start;
	struct timeval	current;
	int				elapsed_time;

	elapsed_time = 0;
	gettimeofday(&start, NULL);
	while (elapsed_time < time_to_wait)
	{
		gettimeofday(&current, NULL);
		elapsed_time = (current.tv_sec - start.tv_sec) * 1000000L \
		+ (current.tv_usec - start.tv_usec);
		usleep(100);
	}
}

void	ft_compute_msec(struct timeval *tv, long long int *msec, t_philo *philo)
{
	gettimeofday(tv, NULL);
	pthread_mutex_lock(philo->mutex_last_meal);
	*msec = (tv->tv_sec * 1000) + (tv->tv_usec / 1000) - philo->time_last_meal;
	pthread_mutex_unlock(philo->mutex_last_meal);
}
