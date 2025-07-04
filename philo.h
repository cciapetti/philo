/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:50:48 by cciapett          #+#    #+#             */
/*   Updated: 2025/07/04 13:09:46 by cciapett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_input_var
{
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times;
	int	flag_optional;
}	t_input;

typedef struct s_philo
{
	int					id;
	long long int		time_last_meal;
	long long int		t0;
	int					is_dead;
	int					finish_to_eat;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*mutex_is_dead;
	pthread_mutex_t		*mutex_last_meal;
	pthread_mutex_t		*mutex_finish_to_eat;
	t_input				*input;
}	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*last_meal;
	pthread_mutex_t	*finish_to_eat;
}	t_mutex;

//MAIN_UTILS.C
int		ft_atoi(const char *nptr);

//PHILO.C
void	ft_create_philo(t_input *input);
void	*do_things(void *arg);

//PHILO_UTILS.C
void	ft_threads(t_input *inp, t_philo **phi, pthread_t *th, \
	pthread_t *death);

//EAT.C
void	ft_eat(t_philo *philo);
void	ft_unlock_fork(t_philo *philo);
void	print_message(t_philo *philo, struct timeval *tv, char *message);

//SLEEP.C
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	my_usleep(int time_to_wait);
void	ft_compute_msec(struct timeval *tv, long long int *msec, \
	t_philo *philo);

//DEATH.C
void	*check_death(void *arg);

//ONE_PHILO.C
void	one_philo(t_input *input);