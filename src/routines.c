/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:06:46 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/10/26 00:07:40 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void sleeping_routine(t_args *philo_data)
{
	if(philo_data->shared->stop_program == NO)
		printf("%li %i is sleeping\n", get_elapsed_time(philo_data-> start_time), philo_data->philo_id);
	usleep(philo_data->time_to_sleep * 1000);
	is_philo_dead_check(philo_data);
}

void eating_routine(t_args *philo_data)
{
	long elapsed_time;
	
	is_philo_dead_check(philo_data);
	elapsed_time = get_elapsed_time(philo_data-> start_time);
	//printf("%li %i has taken a fork\n", elapsed_time, philo_data->philo_id);
	if(philo_data->shared->stop_program == NO)
		printf(GREEN"%li %i is eating\n"RESET, elapsed_time, philo_data->philo_id);
	usleep(philo_data->time_to_eat * 1000);
}

void thinking_routine(t_args *philo_data)
{
	if(philo_data->shared->stop_program == NO)
		printf("%li %i is thinking\n", get_elapsed_time(philo_data-> start_time), philo_data->philo_id);
	is_philo_dead_check(philo_data);
}

void *routine_even(void *arg)
{
	t_args *philo_data =(t_args *) arg;
	//long elapsed_time;
	//long death_time;
	
	while(1)
	{
			sleeping_routine(philo_data);

			eating_routine(philo_data);

			thinking_routine(philo_data);

			if(philo_data->shared->stop_program == NO)
				printf("value philo_data->shared-> stop Program is: NO\n");
			else
				printf("value philo_data->shared-> stop Program is: YES\n");
			if (stop_program_check(philo_data) == 0)
				break;
	}
	free(arg);
	return NULL;
}

void *routine_odd(void *arg)
{
	t_args *philo_data =(t_args *) arg;
	while(1)
	{
			eating_routine(philo_data);
			//stop_program_check(philo_data);
			sleeping_routine(philo_data);
			//stop_program_check(philo_data);
			thinking_routine(philo_data);
			if(philo_data->shared->stop_program == NO)
				printf("value philo_data->shared-> stop Program is: NO\n");
			else
				printf("value philo_data->shared-> stop Program is: YES\n");
			if (stop_program_check(philo_data) == 0)
				break;
	}
	free(arg);
	return NULL;
}
