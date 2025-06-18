/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:50:48 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/18 18:47:56 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_input_var
{
    int num_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times;
}   t_input_var;

typedef struct s_philo
{
    int                 id;
    int                 time_to_die;
    long long int       time_last_meal;
    int                 time_spleeping;
    int                 time_dying;
    long long int       t0;
    pthread_mutex_t     *left_fork;
    pthread_mutex_t     *right_fork;
    t_input_var         *input;
}   t_philo;


//MAIN_UTILS.C
int     ft_atoi(const char *nptr);

//PHILO.C
void    ft_create_philo(t_input_var *input);

//ROUTINE.C
void    ft_lock_forks(t_philo *philo);