/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:51:06 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/07 17:18:22 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_positive(t_input *input)
{
	if (input->num_philo <= 0)
		return (1);
	if (input->time_to_die < 0)
		return (1);
	if (input->time_to_eat < 0)
		return (1);
	if (input->time_to_sleep < 0)
		return (1);
	if (input->number_of_times <= 0 && input->flag_optional == 1)
		return (1);
	return (0);
}

static int	ft_initialize_input(t_input *input, int ac, char **av)
{
	if (ac == 5)
	{
		input->num_philo = ft_atoi(av[1]);
		input->time_to_die = ft_atoi(av[2]);
		input->time_to_eat = ft_atoi(av[3]);
		input->time_to_sleep = ft_atoi(av[4]);
		input->flag_optional = 0;
		input->number_of_times = -1;
	}
	else if (ac == 6)
	{
		input->num_philo = ft_atoi(av[1]);
		input->time_to_die = ft_atoi(av[2]);
		input->time_to_eat = ft_atoi(av[3]);
		input->time_to_sleep = ft_atoi(av[4]);
		input->flag_optional = 1;
		input->number_of_times = ft_atoi(av[5]);
	}
	if (ft_check_positive(input) == 1)
		return (1);
	return (0);
}

int	ft_check_input(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i] != NULL)
	{
		if (av[i][0] == '\0')
			return (1);
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (1);
			j++;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (ac != 5 && ac != 6)
	{
		ft_error_message();
		return (free(input), 0);
	}
	if (ft_check_input(av) == 1)
	{
		ft_error_message2();
		return (free(input), 0);
	}
	if (ft_initialize_input(input, ac, av) == 1)
	{
		ft_error_message2();
		return (free(input), 0);
	}
	ft_create_philo(input);
	free(input);
}
