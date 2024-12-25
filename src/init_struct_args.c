/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:57:31 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/21 17:41:09 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#include <pthread.h>
#include <stdlib.h>

void	ft_destroy_mutexes(t_args *philo_data, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philo)
		pthread_mutex_destroy(&philo_data[i++].l_fork);
	pthread_mutex_destroy(&shared->death);
	pthread_mutex_destroy(&shared->stop);
	pthread_mutex_destroy(&shared->print);
	pthread_mutex_destroy(&shared->eating);
}

static void	init_mutex(t_shared *shared)
{
	if (pthread_mutex_init(&shared->death, NULL) != 0)
	{
		perror("Failed to initialize death");
		exit(EXIT_FAILURE);
	}
	if (pthread_mutex_init(&shared->print, NULL) != 0)
	{
		perror("Failed to initialize print");
		exit(EXIT_FAILURE);
	}
	if (pthread_mutex_init(&shared->stop, NULL) != 0)
	{
		perror("Failed to initialize stop");
		exit(EXIT_FAILURE);
	}
	if (pthread_mutex_init(&shared->eating, NULL) != 0)
	{
		perror("Failed to initialize eating_times");
		exit(EXIT_FAILURE);
	}
}

void	init_shared(t_shared *shared, t_args *data)
{
	init_mutex(shared);
	shared->is_dead = 0;
	shared->stop_program = 0;
	shared->stop_printing = NO;
	shared->turn = shared->n_philo;
	shared->philo_data = data;
}

void	arg_data_init(t_args *data, t_shared *shared, char **argv)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	shared->n_philo = ft_atoi(argv[1]);
	if (shared->n_philo == 1)
		print_one_death(data, shared);
	if (argv[5])
		data->meals = ft_atoi(argv[5]);
	else
		data->meals = -1;
	data->start_time = get_time();
	data->previous_eat_time = data -> start_time;
	data->philo_id = 0;
	data->shared = shared;
	data -> set_position = YES;
	data ->position = 1;
	data->r_fork = NULL;
	data->dead = NO;
	data->stop = NO;
	init_shared(shared, data);
}
