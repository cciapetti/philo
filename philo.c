/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:34:23 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/19 12:49:53 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    ft_routine(t_philo *philo, struct timeval  *tv)
{
    long long int   millisec;

    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->time_last_meal;
    if (millisec < philo->input->time_to_die)
        ft_eat(philo, tv);
    else
        printf("%d\n died", philo->id);
    ft_unlock_fork(philo);
    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->time_last_meal;
    if (millisec < philo->input->time_to_die)
        ft_sleep(philo, tv);
    else
        printf("%d\n died", philo->id);
    gettimeofday(tv, NULL);
    millisec = tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->time_last_meal;
    if (millisec < philo->input->time_to_die)
        ft_think(philo, tv);
    else
        printf("%d died\n", philo->id);
}

void    *do_things(void *arg)
{
    struct timeval  *tv;
    int             i;

    i = -1;
    tv = malloc(sizeof(struct timeval));
    t_philo *philo = (t_philo *)arg;
    gettimeofday(tv, NULL);
    philo->t0 = tv->tv_sec * 1000 + tv->tv_usec / 1000;
    philo->time_last_meal = philo->t0;
    if (philo->input->number_of_times == -1)
    {
        while (tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->time_last_meal < philo->input->time_to_die)
            ft_routine(philo, tv);
    }
    else
    {
        while ((tv->tv_sec * 1000 + tv->tv_usec / 1000 - philo->time_last_meal < philo->input->time_to_die) && ++i < philo->input->num_philo)
            ft_routine(philo, tv);
    }
}

void    ft_init_philo(t_philo **philo, t_input_var *input, pthread_mutex_t *fork)
{
    int i;

    i = -1;
    while (++i < input->num_philo)
    {
        philo[i]->id = i;
        philo[i]->time_to_die = input->time_to_die;
        philo[i]->time_dying = 0;
        philo[i]->time_last_meal = 0;
        philo[i]->time_spleeping = 0;
        philo[i]->t0 = 0;
        philo[i]->input = input;
        if (i == 0)
        {
            philo[i]->left_fork = &fork[i];
            philo[i]->right_fork = &fork[input->num_philo - 1];
        }
        else
        {
            philo[i]->left_fork = &fork[i];
            philo[i]->right_fork = &fork[i - 1];
        }
    }
}

void    ft_create_philo(t_input_var *input)
{
    pthread_mutex_t fork[input->num_philo];
    t_philo         *philo[input->num_philo];
    pthread_t       thread[input->num_philo];
    int             i;

    i = -1;
    while (++i < input->num_philo)
        philo[i] = malloc(sizeof(t_philo));
    i = -1;
    while (++i < input->num_philo)
        pthread_mutex_init(&fork[i], NULL);
    ft_init_philo(philo, input, fork);
    i = -1;
    while (++i < input->num_philo)
        if (pthread_create(&thread[i], NULL, do_things, philo[i]) != 0)
            return ;
    i = -1;
    while (++i < input->num_philo)
        if (pthread_join(thread[i], NULL) != 0)
            return ;
    i = -1;
    while (++i < input->num_philo)
        pthread_mutex_destroy(&fork[i]);
}
