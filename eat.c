/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:15:29 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/19 12:42:04 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_lock_fork_even(t_philo *philo, struct timeval *tv)
{
    long long int   millisec;

    pthread_mutex_lock(philo->left_fork);
    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->t0;
    printf("%llu %d has taken a fork\n", millisec, philo->id);
    pthread_mutex_lock(philo->right_fork);
    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->t0;
    printf("%llu %d has taken a fork\n", millisec, philo->id);
    printf("%llu %d is eating\n", millisec, philo->id);
    usleep(philo->input->time_to_eat * 1000);
    gettimeofday(tv, NULL);
    philo->time_last_meal = tv->tv_sec * 1000 + tv->tv_usec / 1000;
}

void ft_lock_fork_odd(t_philo *philo, struct timeval *tv)
{
    long long int   millisec;

    pthread_mutex_lock(philo->right_fork);
    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->t0;
    printf("%llu %d has taken a fork\n", millisec, philo->id);
    pthread_mutex_lock(philo->left_fork);
    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->t0;
    printf("%llu %d has taken a fork\n", millisec, philo->id);
    printf("%llu %d is eating\n", millisec, philo->id);
    usleep(philo->input->time_to_eat * 1000);
    gettimeofday(tv, NULL);
    philo->time_last_meal = tv->tv_sec * 1000 + tv->tv_usec / 1000;
}

void    ft_eat(t_philo *philo, struct timeval *tv)
{
    if (philo->id % 2 == 0)
        ft_lock_fork_even(philo, tv);
    else if (philo->id % 2 == 1)
    {
        usleep(100);
        ft_lock_fork_odd(philo, tv);
    }

}

void    ft_unlock_fork(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
