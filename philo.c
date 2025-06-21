/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:34:23 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/21 12:55:17 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    ft_routine(t_philo *philo)
{
    ft_eat(philo);
    ft_unlock_fork(philo);
    pthread_mutex_lock(&philo->mutex_is_dead);
    if (philo->is_dead == 1)
    {
        pthread_mutex_unlock(&philo->mutex_is_dead);
        return ;   
    }
    pthread_mutex_unlock(&philo->mutex_is_dead); 
    ft_sleep(philo);
    pthread_mutex_lock(&philo->mutex_is_dead);
    if (philo->is_dead == 1)
    {
        pthread_mutex_unlock(&philo->mutex_is_dead);
        return ;   
    }
    pthread_mutex_unlock(&philo->mutex_is_dead);
    ft_think(philo);
    pthread_mutex_lock(&philo->mutex_is_dead);
    if (philo->is_dead == 1)
    {
        pthread_mutex_unlock(&philo->mutex_is_dead);
        return ;   
    }
    pthread_mutex_unlock(&philo->mutex_is_dead);
}

void    *do_things(void *arg)
{
    int             i;

    i = -1;
    t_philo *philo = (t_philo *)arg;
    if (philo->input->number_of_times == -1)
    {
        if (philo->id % 2 == 0)
            usleep(100);
        while (1)
        {
            pthread_mutex_lock(&philo->mutex_is_dead);
            if (philo->is_dead == 1)
                return (pthread_mutex_unlock(&philo->mutex_is_dead), NULL);
            pthread_mutex_unlock(&philo->mutex_is_dead);
            ft_routine(philo);
        }
    }
    else
    {
        if (philo->id % 2 == 0)
            usleep(100);
        while (++i < philo->input->number_of_times)
        {
            pthread_mutex_lock(&philo->mutex_is_dead);
            if (philo->is_dead == 1)
                return (pthread_mutex_unlock(&philo->mutex_is_dead), NULL);
            pthread_mutex_unlock(&philo->mutex_is_dead);
            ft_routine(philo);
        }
        pthread_mutex_lock(&philo->mutex_is_dead);
        philo->is_dead = 2;
        pthread_mutex_unlock(&philo->mutex_is_dead);
    }
    return (NULL);
}

void    ft_init_philo(t_philo **philo, t_input_var *input, pthread_mutex_t *fork)
{
    int i;
    struct timeval tv;

    i = -1;
    while (++i < input->num_philo)
    {
        philo[i]->id = i;
        philo[i]->time_to_die = input->time_to_die;
        philo[i]->time_dying = 0;
        gettimeofday(&tv, NULL);
        philo[i]->t0 = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
        philo[i]->time_last_meal = philo[i]->t0;
        philo[i]->time_spleeping = 0;
        philo[i]->is_dead = 0;
        pthread_mutex_init(&philo[i]->mutex_is_dead, NULL);
        pthread_mutex_init(&philo[i]->mutex_last_meal, NULL);
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

    if (input->num_philo == 1)
    {
        one_philo(input);
        return ;
    }
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
    i = -1;
    while (++i < input->num_philo)
        free(philo[i]);
}
