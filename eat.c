/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:15:29 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/20 17:13:12 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_message(t_philo *philo, struct timeval tv, char *message)
{
    long long int   millisec;

    pthread_mutex_lock(&philo->mutex_is_dead);
    gettimeofday(&tv, NULL);
    millisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo->t0;
    if (philo->is_dead == 0)
        printf("%llu %d %s\n", millisec, philo->id, message);
    pthread_mutex_unlock(&philo->mutex_is_dead);
}

void ft_lock_fork(t_philo *philo)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    pthread_mutex_lock(philo->left_fork);
    print_message(philo, tv, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_message(philo, tv, "has taken a fork");
    print_message(philo, tv, "is eating");
    pthread_mutex_lock(&philo->mutex_is_dead);
    gettimeofday(&tv, NULL);
    philo->time_last_meal = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    pthread_mutex_unlock(&philo->mutex_is_dead);
    usleep(philo->input->time_to_eat * 1000);
}

void ft_lock_fork_first(t_philo *philo)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    pthread_mutex_lock(philo->right_fork);
    print_message(philo, tv, "has taken a fork");
    pthread_mutex_lock(philo->left_fork);
    print_message(philo, tv, "has taken a fork");
    print_message(philo, tv, "is eating");
    pthread_mutex_lock(&philo->mutex_is_dead);
    gettimeofday(&tv, NULL);
    philo->time_last_meal = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    pthread_mutex_unlock(&philo->mutex_is_dead);
    usleep(philo->input->time_to_eat * 1000);
}

void    ft_eat(t_philo *philo)
{
    if (philo->id != 0)
        ft_lock_fork(philo);
    else if (philo-> id == 0)
        ft_lock_fork_first(philo);
    // if (philo->id % 2 == 0)
    //     ft_lock_fork(philo, tv);
    // else if (philo->id % 2 == 1)
    // {
    //     usleep(100);
    //     ft_lock_fork_first(philo, tv);
    // }
}

void    ft_unlock_fork(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
