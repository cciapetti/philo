/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:51:06 by cciapett          #+#    #+#             */
/*   Updated: 2025/06/18 15:35:49 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    ft_error_message(void)
{
    printf("number_of_philosophers\ntime_to_die\ntime_to_eat\n");
    printf("time_to_sleep\n[number_of_times_each_philosopher_must_eat]\n");
}

static void    ft_initialize_input(t_input_var *input, int ac, char **av)
{
    if (ac == 5)
    {
        input->num_philo = ft_atoi(av[1]);
        input->time_to_die = ft_atoi(av[2]);
        input->time_to_eat = ft_atoi(av[3]);
        input->time_to_sleep = ft_atoi(av[4]);
        input->number_of_times = -1;
    }
    else if (ac == 6)
    {
        input->num_philo = ft_atoi(av[1]);
        input->time_to_die = ft_atoi(av[2]);
        input->time_to_eat = ft_atoi(av[3]);
        input->time_to_sleep = ft_atoi(av[4]);
        input->number_of_times = ft_atoi(av[5]);
    }
}

int main(int ac, char **av)
{
    t_input_var *input;
    int         i;

    i = -1;
    input = malloc(sizeof(t_input_var));
    if (ac != 5 && ac != 6)
    {
        ft_error_message();
        return (free(input), 0);
    }
    else
        ft_initialize_input(input, ac, av);
    ft_create_philo(input);
    free(input);
}
