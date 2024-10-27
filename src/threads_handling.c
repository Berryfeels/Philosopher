/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:24:35 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/10/26 00:02:19 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void ft_destroy_mutexes(t_args *data)
{
	int i;

	i = 0;
	while(i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->shared->fork[i++]);
	}
	pthread_mutex_destroy(&data->shared->death_mutex);
}

int	ft_join_threads(pthread_t *philo, t_args *data)
{
	int	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philo[i], NULL) != 0)
			ft_exit_error(EXIT_ERROR_THREAD); // Error check
		i++;
	}
	
	return (0);
}

static void ft_create_threads(t_args *philo_data, pthread_t *philo)
{
	if (philo_data->number_of_philosophers % 2)
	{
		if (pthread_create(philo, NULL, routine_odd, (void *)philo_data) != 0)
			ft_exit_error(EXIT_ERROR_THREAD);
	}
	if (!(philo_data->number_of_philosophers % 2))
	{
		if (pthread_create(philo, NULL, routine_even, (void *)philo_data) != 0)
			ft_exit_error(EXIT_ERROR_THREAD);
	}

	printf("Philli[%i] was created\n", philo_data->philo_id);
}

void	ft_threads(t_args *data)
{
	pthread_t philo[data->number_of_philosophers];
	pthread_t death_supervisor;
	t_args *philo_data;
	int i;

	if (pthread_create(&death_supervisor, NULL, supervising, (void *)data->shared) != 0)
		exit(EXIT_ERROR_THREAD);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo_data = (t_args *)malloc(sizeof(t_args));
		if (!philo_data)
			break;
		data->philo_id = i + 1;
		*philo_data = *data;
		ft_create_threads(philo_data, &philo[i]);
		
		i++;
	}
	ft_join_threads(philo, data);
	if (pthread_join(death_supervisor, NULL) != 0)
			ft_exit_error(EXIT_ERROR_THREAD);
	ft_destroy_mutexes(data);
	
}
