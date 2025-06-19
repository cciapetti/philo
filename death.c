/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:54:02 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/19 16:28:17 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_all_one(t_philo **philo, int tot)
{
    int i;

    i = 0;
    while (i < tot)
    {
        philo[i]->is_dead = 1;
        i++;
    }
}

void    *check_death(void *arg)
{
    struct timeval  *tv;
    int             i;
    int             tot;
    long long int   millisec;

    t_philo **philo = (t_philo **)arg;
    tv = malloc(sizeof(struct timeval));
    tot = philo[0]->input->num_philo;
    while (1)
    {
        i = 0;
        while (i < tot)
        {
            gettimeofday(tv, NULL);
            pthread_mutex_lock(&philo[i]->mutex_is_dead);
            millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo[i]->time_last_meal;
            if (millisec > philo[i]->input->time_to_die)
            {
                printf("%llu %d is dead\n", tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo[i]->t0, philo[i]->id);
                set_all_one(philo, tot);
                return (NULL);
            }
            pthread_mutex_unlock(&philo[i]->mutex_is_dead);
        }
    }
}
