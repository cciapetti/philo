/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:46:22 by chiara_ciap       #+#    #+#             */
/*   Updated: 2025/07/07 17:25:09 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_threads(t_input *inp, t_philo **phi, pthread_t *th, pthread_t *death)
{
	int	i;

	i = -1;
	while (++i < inp->num_philo)
		if (pthread_create(&th[i], NULL, do_things, phi[i]) != 0)
			return ;
	if (pthread_create(death, NULL, check_death, phi) != 0)
		return ;
	i = -1;
	while (++i < inp->num_philo)
		if (pthread_join(th[i], NULL) != 0)
			return ;
	if (pthread_join(*death, NULL) != 0)
		return ;
}

void	ft_unlock_first_left(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_unlock_first_right(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
