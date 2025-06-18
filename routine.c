/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:15:29 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/18 18:49:53 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_lock_forks(t_philo *philo)
{
    struct timeval  *tv;
    long long int   millisec;

    tv = malloc(sizeof(struct timeval));
    printf("prima della fork sinistra\n");
    pthread_mutex_lock(philo->left_fork);
    gettimeofday(tv, NULL);
    // printf("bo: %lu", tv->tv_sec * 1000 + tv->tv_usec / 1000);
    // printf("bo: %llu", philo->t0);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->t0;
    // printf("MILLISEC: %llu\n", millisec);
    printf("%llu %d has taken a fork\n", millisec, philo->id);
    printf("prima della fork destra\n");
    pthread_mutex_lock(philo->right_fork);
    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->t0;
    printf("%llu %d has taken a fork\n", millisec, philo->id);
}
