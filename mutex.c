/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:18:50 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/07 17:19:13 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_mutex(t_mutex *mutex, t_input *input)
{
	int	i;

	i = -1;
	mutex->fork = malloc(sizeof(pthread_mutex_t) * input->num_philo);
	mutex->dead = malloc(sizeof(pthread_mutex_t));
	mutex->last_meal = malloc(sizeof(pthread_mutex_t) * input->num_philo);
	mutex->finish_to_eat = malloc(sizeof(pthread_mutex_t) * input->num_philo);
	while (++i < input->num_philo)
		pthread_mutex_init(&mutex->fork[i], NULL);
	pthread_mutex_init(mutex->dead, NULL);
	i = -1;
	while (++i < input->num_philo)
		pthread_mutex_init(&mutex->last_meal[i], NULL);
	i = -1;
	while (++i < input->num_philo)
		pthread_mutex_init(&mutex->finish_to_eat[i], NULL);
}

void	ft_destroy_mutex(t_mutex *mutex, t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->num_philo)
		pthread_mutex_destroy(&mutex->fork[i]);
	pthread_mutex_destroy(mutex->dead);
	i = -1;
	while (++i < input->num_philo)
		pthread_mutex_destroy(&mutex->last_meal[i]);
	i = -1;
	while (++i < input->num_philo)
		pthread_mutex_destroy(&mutex->finish_to_eat[i]);
	free(mutex->fork);
	free(mutex->dead);
	free(mutex->last_meal);
	free(mutex->finish_to_eat);
}
