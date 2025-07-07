/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:14:07 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/07 17:16:41 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 0;
	result = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign++;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		result = (result * 10) + (nptr[i] - 48);
		i++;
	}
	if (sign == 1)
		return (result * (-1));
	else
		return (result);
}

int	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
		;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_error_message(void)
{
	ft_putstr_fd("number_of_philosophers\ntime_to_die\ntime_to_eat\n", 2);
	ft_putstr_fd("time_to_sleep\n[number_of_times_each_philosopher\
_must_eat]\n", 2);
}

void	ft_error_message2(void)
{
	ft_putstr_fd("Error: a postive numeric argument is required\n", 2);
}
