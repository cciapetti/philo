/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:54:02 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/04 14:58:27 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_all_one(t_philo **philo, int index, struct timeval *tv)
{
	int				i;
	int				tot;
	long long int	msec;

	msec = (tv->tv_sec * 1000) + (tv->tv_usec / 1000);
	i = -1;
	tot = philo[0]->input->num_philo;
	pthread_mutex_lock((*philo)->mutex_is_dead);
	while (++i < tot)
		philo[i]->is_dead = 1;
	printf("%lld %d died\n", msec - philo[index]->t0, philo[index]->id);
	pthread_mutex_unlock((*philo)->mutex_is_dead);
	return (0);
}

static int	ft_check_all_eat(t_philo **philo)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < philo[0]->input->num_philo)
	{
		pthread_mutex_lock(philo[i]->mutex_finish_to_eat);
		if (philo[i]->finish_to_eat == 1)
			j++;
		pthread_mutex_unlock(philo[i]->mutex_finish_to_eat);
	}
	if (j == philo[0]->input->num_philo)
	{
		i = -1;
		while (++i < philo[0]->input->num_philo)
		{
			pthread_mutex_lock(philo[i]->mutex_finish_to_eat);
			philo[i]->finish_to_eat = 2;
			pthread_mutex_unlock(philo[i]->mutex_finish_to_eat);
		}
		return (1);
	}
	return (0);
}


void	*check_death(void *arg)
{
	struct timeval	tv;
	int				i;
	long long int	millisec;
	t_philo			**philo;

	philo = (t_philo **)arg;
	usleep(100);
	while (1)
	{
		usleep(100);
		i = -1;
		if (ft_check_all_eat(philo) == 1)
			return (NULL);
		while (++i < philo[0]->input->num_philo)
		{
			ft_compute_msec(&tv, &millisec, philo[i]);
			if (millisec >= philo[i]->input->time_to_die)
				return (set_all_one(philo, i, &tv), NULL);
		}
	}
	return (NULL);
}
