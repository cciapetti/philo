/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:54:02 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/01 19:09:59 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_all_one(t_philo **philo)
{
	int	i;
	int	tot;

	i = -1;
	tot = philo[0]->input->num_philo;
	while (++i < tot)
	{
		pthread_mutex_lock((*philo)->mutex_is_dead);
		philo[i]->is_dead = 1;
		pthread_mutex_unlock((*philo)->mutex_is_dead);
	}
	return (0);
}

static int	ft_check_all_eat(t_philo **philo)
{
	int	i;
	int	j;
	int	tot;

	i = -1;
	j = 0;
	tot = philo[0]->input->num_philo;
	while (++i < tot)
	{
		pthread_mutex_lock(philo[i]->mutex_is_dead);
		if (philo[i]->is_dead == 2)
			j++;
		pthread_mutex_unlock(philo[i]->mutex_is_dead);
	}
	if (j == tot)
		return (1);
	return (0);
}

void	philo_died(t_philo *philo, struct timeval *tv)
{
	long long int	msec;

	msec = (tv->tv_sec * 1000) + (tv->tv_usec / 1000);
	pthread_mutex_lock(philo->mutex_is_dead);
	philo->is_dead = 1;
	printf("%lld %d died\n", msec - philo->t0, philo->id);
	pthread_mutex_unlock(philo->mutex_is_dead);
}

void	ft_init(int *i)
{
	my_usleep(100);
	*i = -1;
}

void	*check_death(void *arg)
{
	struct timeval	tv;
	int				i;
	long long int	millisec;
	t_philo			**philo;

	philo = (t_philo **)arg;
	my_usleep(100);
	while (1)
	{
		ft_init(&i);
		if (ft_check_all_eat(philo) == 1)
		{
			printf("FILOSOFI CHE HANNO MANGIATO\n");
			return (NULL);	
		}
		while (++i < philo[0]->input->num_philo)
		{
			ft_compute_msec(&tv, &millisec, philo[i]);
			if (millisec >= philo[i]->input->time_to_die)
			{
				philo_died(philo[i], &tv);
				set_all_one(philo);
				return (NULL);
			}
		}
	}
	return (NULL);
}
