/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:20:30 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/04 14:55:28 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo_exe(void *arg)
{
	long long int	millisec;
	struct timeval	tv;
	long long int	t0;
	t_input			*input;

	input = (t_input *)arg;
	gettimeofday(&tv, NULL);
	t0 = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	millisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - t0;
	printf("%lld %d has taken a fork\n", millisec, 0);
	usleep(input->time_to_die * 1000);
	printf("%d %d died\n", input->time_to_die, 0);
	return (NULL);
}

void	one_philo(t_input *input)
{
	pthread_t	one_philo;

	if (pthread_create(&one_philo, NULL, one_philo_exe, input) != 0)
		return ;
	if (pthread_join(one_philo, NULL) != 0)
		return ;
}
