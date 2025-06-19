/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:55:46 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/19 16:28:03 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_sleep(t_philo *philo, struct timeval *tv)
{
    pthread_mutex_lock(&philo->mutex_is_dead);
    print_message(philo, tv, "is sleeping");
    pthread_mutex_unlock(&philo->mutex_is_dead);
    usleep(philo->input->time_to_sleep * 1000);
}

void    ft_think(t_philo *philo, struct timeval *tv)
{
    pthread_mutex_lock(&philo->mutex_is_dead);
    print_message(philo, tv, "is thinking");
    pthread_mutex_unlock(&philo->mutex_is_dead);
}
