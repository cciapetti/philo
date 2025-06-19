/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:34:23 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/19 16:27:24 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    ft_routine(t_philo *philo, struct timeval  *tv)
{
    if (philo->is_dead == 0)
    {
        ft_eat(philo, tv);
        ft_unlock_fork(philo);   
    }
    if (philo->is_dead == 0)
        ft_sleep(philo, tv);
    if (philo->is_dead == 0)
        ft_think(philo, tv);
}

void    *do_things(void *arg)
{
    struct timeval  *tv;
    int             i;

    i = -1;
    tv = malloc(sizeof(struct timeval));
    t_philo *philo = (t_philo *)arg;
    gettimeofday(tv, NULL);
    pthread_mutex_lock(&philo->mutex_is_dead);
    philo->t0 = tv->tv_sec * 1000 + tv->tv_usec / 1000;
    philo->time_last_meal = philo->t0;
    pthread_mutex_unlock(&philo->mutex_is_dead);
    if (philo->input->number_of_times == -1)
        while (1)
        {
            if (philo->is_dead == 1)
                return (NULL);
            ft_routine(philo, tv);
        }
    else
        while (++i < philo->input->num_philo)
        {
            if (philo->is_dead == 1)
                return (NULL);
            ft_routine(philo, tv);
        }
    return (NULL);
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
        philo[i]->is_dead = 0;
        pthread_mutex_init(&philo[i]->mutex_is_dead, NULL);
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
    pthread_t       death;
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
    if (pthread_create(&death, NULL, check_death, philo) != 0)
        return ;
    i = -1;
    while (++i < input->num_philo)
        if (pthread_join(thread[i], NULL) != 0)
            return ;
    if (pthread_join(death, NULL) != 0)
         return ;
    i = -1;
    while (++i < input->num_philo)
        pthread_mutex_destroy(&fork[i]);
}
