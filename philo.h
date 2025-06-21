/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:50:48 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/21 12:34:29 by cciapett         ###   ########.fr       */
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
    int flag_optional;
}   t_input_var;

typedef struct s_philo
{
    int                 id;
    int                 time_to_die;
    long long int       time_last_meal;
    int                 time_spleeping;
    int                 time_dying;
    long long int       t0;
    int                 is_dead;
    pthread_mutex_t     *left_fork;
    pthread_mutex_t     *right_fork;
    pthread_mutex_t     mutex_is_dead;
    pthread_mutex_t     mutex_last_meal;
    t_input_var         *input;
}   t_philo;


//MAIN_UTILS.C
int     ft_atoi(const char *nptr);

//PHILO.C
void    ft_create_philo(t_input_var *input);

//EAT.C
void    ft_eat(t_philo *philo);
void    ft_unlock_fork(t_philo *philo);
void    print_message(t_philo *philo, struct timeval tv, char *message);

//SLEEP.C
void    ft_sleep(t_philo *philo);
void    ft_think(t_philo *philo);

//DEATH.C
void    *check_death(void *arg);

//ONE_PHILO.C
void    one_philo(t_input_var *input);