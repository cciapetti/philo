/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:54:02 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/20 16:42:19 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    set_all_one(t_philo **philo, int tot)
{
    int i;

    i = 0;
    while (i < tot)
    {
        philo[i]->is_dead = 1;
        i++;
    }
}

static int ft_check_all_eat(t_philo **philo, int tot)
{
    int i;
    int j;

    i = -1;
    j = 0;
    while (++i < tot)
    {
        if (philo[i]->is_dead == 2)
            j++;
    }
    if (j == tot)
        return (1);
    return (0);
}

void    *check_death(void *arg)
{
    struct timeval  *tv;
    int             i;
    int             tot;
    long long int   millisec;
    int             num_meal;

    t_philo **philo = (t_philo **)arg;
    tv = malloc(sizeof(struct timeval));
    tot = philo[0]->input->num_philo;
    num_meal = 0;
    usleep(100);
    while (1)
    {
        usleep(10);
        i = -1;
        while (++i < tot)
        {
            pthread_mutex_lock(&philo[i]->mutex_is_dead);
            gettimeofday(tv, NULL);
            millisec = (tv->tv_sec * 1000) + (tv->tv_usec / 1000) - philo[i]->time_last_meal;
            if (ft_check_all_eat(philo, tot) == 1)
                return (pthread_mutex_unlock(&philo[i]->mutex_is_dead), free(tv), NULL);
                
            if (millisec > philo[i]->input->time_to_die)
            {
                printf("%llu %d died\n", (tv->tv_sec * 1000) + (tv->tv_usec / 1000) - philo[i]->t0, philo[i]->id);
                set_all_one(philo, tot);
                pthread_mutex_unlock(&philo[i]->mutex_is_dead);
                return (free(tv), NULL);
            }
            pthread_mutex_unlock(&philo[i]->mutex_is_dead);
        }
    }
    return (free(tv), NULL);
}
