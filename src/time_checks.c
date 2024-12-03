/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:09:26 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/03 21:59:57 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_if_i_can_eat(t_args *philo_data)
{
	pthread_mutex_lock(&philo_data->shared->eating);
	if (philo_data->p_round <= philo_data->shared->a_round)
		philo_data->can_i_eat = YES;
	else if (philo_data->p_round > philo_data->shared->a_round)
		philo_data->can_i_eat = NO;
	pthread_mutex_unlock(&philo_data->shared->eating);
}

int	stop_program_check(t_args *philo_data)
{
	int stop;

	stop = NO;
	pthread_mutex_lock (&philo_data->shared->stop);
	if (philo_data->shared->stop_program == YES)
		stop = YES;
	pthread_mutex_unlock (&philo_data->shared->stop);
	return (stop);
}

int	dead_check(t_args *philo_data)
{
	int	is_dead;
	int	time_passed_since_last_supper;

	is_dead = NO;
	time_passed_since_last_supper = get_elapsed_supper_time(philo_data);
	pthread_mutex_lock (&philo_data->shared->death);
	if (time_passed_since_last_supper > philo_data->time_to_die &&
        philo_data->shared->is_dead == NO)
	{
		philo_data->shared->is_dead = YES;
		philo_data->shared->dead_philo = philo_data->philo_id;
		pthread_mutex_lock (&philo_data->shared->stop);
		philo_data->shared->stop_program = YES;
		pthread_mutex_unlock (&philo_data->shared->stop);
		is_dead = YES;
		death_message(philo_data);
	}
	pthread_mutex_unlock (&philo_data->shared->death);
	return (is_dead);
}

long	get_elapsed_supper_time(t_args *data)
{
	long	time_passed;

	time_passed = get_elapsed_time(data->previous_eat_time);
	return (time_passed);
}
