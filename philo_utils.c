/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiara_ciapetti <chiara_ciapetti@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:46:22 by chiara_ciap       #+#    #+#             */
/*   Updated: 2025/06/22 22:00:27 by chiara_ciap      ###   ########.fr       */
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
