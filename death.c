/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiara_ciapetti <chiara_ciapetti@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:54:02 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/22 13:14:38 by chiara_ciap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_all_one(t_philo **philo, int tot, int index)
{
	int	i;

	i = -1;
	while (++i < tot)
	{
		if (index != i)
		{
			pthread_mutex_lock(&philo[i]->mutex_is_dead);
			philo[i]->is_dead = 1;
			pthread_mutex_unlock(&philo[i]->mutex_is_dead);
		}
	}
	return (0);
}

static int	ft_check_all_eat(t_philo **philo, int tot)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < tot)
	{
		pthread_mutex_lock(&philo[i]->mutex_is_dead);
		if (philo[i]->is_dead == 2)
			j++;
		pthread_mutex_unlock(&philo[i]->mutex_is_dead);
	}
	if (j == tot)
		return (1);
	return (0);
}

void	*check_death(void *arg)
{
	struct timeval	tv;
	int				i;
	int				tot;
	long long int	millisec;
	t_philo			**philo;

	philo = (t_philo **)arg;
	tot = philo[0]->input->num_philo;
	my_usleep(100);
	while (1)
	{
		my_usleep(100);
		i = -1;
		while (++i < tot)
		{
			if (ft_check_all_eat(philo, tot) == 1)
				return (NULL);
			gettimeofday(&tv, NULL);
			pthread_mutex_lock(&philo[i]->mutex_last_meal);
			millisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo[i]->time_last_meal;
			pthread_mutex_unlock(&philo[i]->mutex_last_meal);
			if (millisec > philo[i]->input->time_to_die)
			{
				pthread_mutex_lock(&philo[i]->mutex_is_dead);
				philo[i]->is_dead = 1;
				set_all_one(philo, tot, i);
				printf("%lld %d died\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo[i]->t0, philo[i]->id);
				pthread_mutex_unlock(&philo[i]->mutex_is_dead);
				return (NULL);
			}
		}
	}
	return (NULL);
}
