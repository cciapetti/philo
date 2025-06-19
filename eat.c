/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:15:29 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/19 16:27:50 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_message(t_philo *philo, struct timeval *tv, char *message)
{
    long long int   millisec;

    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->t0;
    if (philo->is_dead == 0)
        printf("%llu %d %s\n", millisec, philo->id, message);
}

void ft_lock_fork_even(t_philo *philo, struct timeval *tv)
{
    pthread_mutex_lock(&philo->mutex_is_dead);
    pthread_mutex_lock(philo->left_fork);
    print_message(philo, tv, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_message(philo, tv, "has taken a fork");
    print_message(philo, tv, "is eating");
    usleep(philo->input->time_to_eat * 1000);
    gettimeofday(tv, NULL);
    philo->time_last_meal = tv->tv_sec * 1000 + tv->tv_usec / 1000;
    pthread_mutex_unlock(&philo->mutex_is_dead);
}

void ft_lock_fork_odd(t_philo *philo, struct timeval *tv)
{
    pthread_mutex_lock(&philo->mutex_is_dead);
    pthread_mutex_lock(philo->left_fork);
    print_message(philo, tv, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_message(philo, tv, "has taken a fork");
    print_message(philo, tv, "is eating");
    usleep(philo->input->time_to_eat * 1000);
    gettimeofday(tv, NULL);
    philo->time_last_meal = tv->tv_sec * 1000 + tv->tv_usec / 1000;
    pthread_mutex_unlock(&philo->mutex_is_dead);
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
