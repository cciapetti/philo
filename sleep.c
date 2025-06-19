/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:55:46 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/19 12:56:08 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_sleep(t_philo *philo, struct timeval *tv)
{
    long long int   millisec;

    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->t0;
    printf("%llu %d is sleeping\n", millisec, philo->id);
    usleep(philo->input->time_to_sleep * 1000);
    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->time_last_meal;
    if (millisec < philo->input->time_to_die)
        ft_sleep(philo, tv);
    else
        printf("%d died\n", philo->id);
}

void    ft_think(t_philo *philo, struct timeval *tv)
{
    long long int   millisec;

    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->t0;
    printf("%llu %d is thinking\n", millisec, philo->id);
}
