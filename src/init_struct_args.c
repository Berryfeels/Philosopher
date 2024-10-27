/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:57:31 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/10/25 21:37:40 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#include <pthread.h>
#include <stdlib.h>

void	init_shared(t_shared *shared, int num_philosophers) {
	int i;

	// Inizializza tutti i mutex dei fork
	for (i = 0; i < num_philosophers; i++) {
		if (pthread_mutex_init(&shared->fork[i], NULL) != 0) {
			perror("Failed to initialize fork mutex");
			exit(EXIT_FAILURE);
		}
	}

	// Inizializza il mutex per `death_mutex`
	if (pthread_mutex_init(&shared->death_mutex, NULL) != 0) {
		perror("Failed to initialize death mutex");
		exit(EXIT_FAILURE);
	}

	// Inizializza gli altri valori interi
	shared->is_dead = 0;
	shared->stop_program = 0;
	shared->dead_philo = 0;
}

void arg_data_init (t_args *data, t_shared *shared, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	if (data->number_of_philosophers < 2)
		ft_exit_error(EXIT_ERROR_TOO_FEW_PHILOSOPHERS);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else 
		data->number_of_times_each_philosopher_must_eat = 0;
	data->start_time = get_time();
	data->previous_eat_time = data -> start_time;
	printf("Time at start is:%ld\n", (long)data->start_time);
	data->philo_id = 0;
	data->fork_left = 0;
	data->fork_right = 0;
	data->shared = shared;
	init_shared(shared, data->number_of_philosophers);
}