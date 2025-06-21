/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:55:46 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/21 13:11:14 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_sleep(t_philo *philo)
{
    struct timeval tv;

    gettimeofday(&tv , NULL);
    print_message(philo, tv, "is sleeping");
    usleep(philo->input->time_to_sleep * 1000);
}

void    ft_think(t_philo *philo)
{
    struct timeval tv;

    gettimeofday(&tv , NULL);
    print_message(philo, tv, "is thinking");
    usleep(100);
}
