/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:34:23 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/07 17:19:09 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_finish_to_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_finish_to_eat);
	philo->finish_to_eat = 1;
	pthread_mutex_unlock(philo->mutex_finish_to_eat);
	return (0);
}

static int	ft_routine(t_philo *philo, int num_cycle)
{
	pthread_mutex_lock(philo->mutex_is_dead);
	if (philo->is_dead == 1)
		return (pthread_mutex_unlock(philo->mutex_is_dead), 1);
	pthread_mutex_unlock(philo->mutex_is_dead);
	ft_eat(philo);
	ft_unlock_fork(philo);
	if (philo->input->number_of_times != -1)
		if (num_cycle == philo->input->number_of_times - 1)
			if (ft_finish_to_eat(philo) == 0)
				return (1);
	pthread_mutex_lock(philo->mutex_is_dead);
	if (philo->is_dead == 1)
		return (pthread_mutex_unlock(philo->mutex_is_dead), 1);
	pthread_mutex_unlock(philo->mutex_is_dead);
	ft_sleep(philo);
	pthread_mutex_lock(philo->mutex_is_dead);
	if (philo->is_dead == 1)
		return (pthread_mutex_unlock(philo->mutex_is_dead), 1);
	pthread_mutex_unlock(philo->mutex_is_dead);
	ft_think(philo);
	return (0);
}

void	*do_things(void *arg)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	if (philo->input->number_of_times == -1)
	{
		while (1)
		{
			if (ft_routine(philo, i) == 1)
				return (NULL);
		}
	}
	else
	{
		while (++i < philo->input->number_of_times)
		{
			if (ft_routine(philo, i) == 1)
				return (NULL);
		}
	}
	return (NULL);
}

void	ft_init_philo(t_philo **philo, t_input *inp, t_mutex *mutex)
{
	int					i;
	struct timeval		tv;

	i = -1;
	gettimeofday(&tv, NULL);
	while (++i < inp->num_philo)
	{
		philo[i]->id = i + 1;
		philo[i]->t0 = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		philo[i]->time_last_meal = philo[i]->t0;
		philo[i]->is_dead = 0;
		philo[i]->finish_to_eat = 0;
		philo[i]->input = inp;
		philo[i]->right_fork = &mutex->fork[i];
		if (i == 0)
			philo[i]->left_fork = &mutex->fork[inp->num_philo - 1];
		else
			philo[i]->left_fork = &mutex->fork[i - 1];
		philo[i]->mutex_is_dead = mutex->dead;
		philo[i]->mutex_last_meal = &mutex->last_meal[i];
		philo[i]->mutex_finish_to_eat = &mutex->finish_to_eat[i];
	}
}

void	ft_create_philo(t_input *input)
{
	t_philo			**philo;
	pthread_t		*thread;
	pthread_t		death;
	t_mutex			mutex;
	int				i;

	ft_init_mutex(&mutex, input);
	philo = malloc(sizeof(t_philo **) * input->num_philo);
	thread = malloc(sizeof(pthread_t) * input->num_philo);
	if (input->num_philo == 1)
		return (one_philo(input));
	i = -1;
	while (++i < input->num_philo)
		philo[i] = malloc(sizeof(t_philo));
	ft_init_philo(philo, input, &mutex);
	ft_threads(input, philo, thread, &death);
	i = -1;
	ft_destroy_mutex(&mutex, input);
	while (++i < input->num_philo)
		free(philo[i]);
	free(thread);
	free(philo);
}
