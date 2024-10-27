/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:09:26 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/10/26 00:12:53 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int stop_program_check(t_args *philo_data)
{
	pthread_mutex_lock (&philo_data->shared->death_mutex);
	if (philo_data->shared->stop_program == YES)
	{	
		pthread_mutex_unlock (&philo_data->shared->death_mutex);
		return(0);
	}
	pthread_mutex_unlock (&philo_data->shared->death_mutex);
	return(1);
}

void *supervising(void *args)
{
	t_shared *shared;
	
	shared = (t_shared *) args;	
	pthread_mutex_lock (&shared->death_mutex);
	if (shared->is_dead == YES)
	{
		shared->stop_program = YES;
		printf("Stop program ");
		printf(RED"%i died\n"RESET, shared->dead_philo);
	}
	pthread_mutex_unlock (&shared->death_mutex);
	return (NULL);
}

void is_philo_dead_check(t_args *philo_data)
{
	int time_passed_since_last_supper = 0;
	pthread_mutex_lock (&philo_data->shared->death_mutex);
	if ((time_passed_since_last_supper = get_elapsed_supper_time(philo_data)) > philo_data->time_to_die)
	{
		philo_data->shared->is_dead = YES;
		philo_data->shared->dead_philo = philo_data->philo_id;
	}
	printf("time_passed_since_last_supper for %i is: %i\n", philo_data->philo_id, time_passed_since_last_supper);
	pthread_mutex_unlock (&philo_data->shared->death_mutex);
}

long get_elapsed_supper_time(t_args *data)
{
	long time_passed;

	time_passed = get_elapsed_time(data->previous_eat_time);
	data->previous_eat_time = get_time();
	return (time_passed);
}

long get_elapsed_time(long relation_time)
{
    long now;
	long elapsed_time;

	now = get_time();
	elapsed_time = now - relation_time;
    return (elapsed_time);
}

long get_time()
{
	struct timeval current;
	
    gettimeofday(&current, NULL);
    return (current.tv_sec * 1000L) + (current.tv_usec / 1000L);;
}