/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiara_ciapetti <chiara_ciapetti@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:34:23 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/22 21:58:07 by chiara_ciap      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_is_dead);
	if (philo->is_dead == 1)
		return (pthread_mutex_unlock(&philo->mutex_is_dead), 1);
	pthread_mutex_unlock(&philo->mutex_is_dead);
	ft_eat(philo);
	ft_unlock_fork(philo);
	pthread_mutex_lock(&philo->mutex_is_dead);
	if (philo->is_dead == 1)
		return (pthread_mutex_unlock(&philo->mutex_is_dead), 1);
	pthread_mutex_unlock(&philo->mutex_is_dead);
	ft_sleep(philo);
	pthread_mutex_lock(&philo->mutex_is_dead);
	if (philo->is_dead == 1)
		return (pthread_mutex_unlock(&philo->mutex_is_dead), 1);
	pthread_mutex_unlock(&philo->mutex_is_dead);
	ft_think(philo);
	pthread_mutex_lock(&philo->mutex_is_dead);
	if (philo->is_dead == 1)
		return (pthread_mutex_unlock(&philo->mutex_is_dead), 1);
	pthread_mutex_unlock(&philo->mutex_is_dead);
	return (0);
}

void	ft_finish_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_is_dead);
	philo->is_dead = 2;
	pthread_mutex_unlock(&philo->mutex_is_dead);
}

void	*do_things(void *arg)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = (t_philo *)arg;
	if (philo->input->number_of_times == -1)
	{
		if (philo->id % 2 == 0)
			my_usleep(100);
		while (1)
			if (ft_routine(philo) == 1)
				return (NULL);
	}
	else
	{
		if (philo->id % 2 == 0)
			my_usleep(100);
		while (++i < philo->input->number_of_times)
			if (ft_routine(philo) == 1)
				return (NULL);
		ft_finish_to_eat(philo);
	}
	return (NULL);
}

void	ft_init_philo(t_philo **philo, t_input *inp, pthread_mutex_t *fork)
{
	int				i;
	struct timeval	tv;

	i = -1;
	while (++i < inp->num_philo)
	{
		philo[i]->id = i;
		gettimeofday(&tv, NULL);
		philo[i]->t0 = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		philo[i]->time_last_meal = philo[i]->t0;
		philo[i]->is_dead = 0;
		pthread_mutex_init(&philo[i]->mutex_is_dead, NULL);
		pthread_mutex_init(&philo[i]->mutex_last_meal, NULL);
		philo[i]->input = inp;
		if (i == 0)
		{
			philo[i]->left_fork = &fork[i];
			philo[i]->right_fork = &fork[inp->num_philo - 1];
		}
		else
		{
			philo[i]->left_fork = &fork[i];
			philo[i]->right_fork = &fork[i - 1];
		}
	}
}

void	ft_create_philo(t_input *input)
{
	pthread_mutex_t	*fork;
	t_philo			**philo;
	pthread_t		*thread;
	pthread_t		death;
	int				i;

	philo = malloc(sizeof(t_philo **) * input->num_philo);
	fork = malloc(sizeof(pthread_mutex_t) * input->num_philo);
	thread = malloc(sizeof(pthread_t) * input->num_philo);
	if (input->num_philo == 1)
		return (one_philo(input));
	i = -1;
	while (++i < input->num_philo)
		philo[i] = malloc(sizeof(t_philo));
	i = -1;
	while (++i < input->num_philo)
		pthread_mutex_init(&fork[i], NULL);
	ft_init_philo(philo, input, fork);
	ft_threads(input, philo, thread, &death);
	i = -1;
	while (++i < input->num_philo)
		pthread_mutex_destroy(&fork[i]);
	i = -1;
	while (++i < input->num_philo)
		free(philo[i]);
}
