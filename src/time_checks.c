/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:09:26 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/15 21:14:48 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_if_i_can_eat(t_args *philo_data)
{
	pthread_mutex_lock(&philo_data->shared->eating);
	
	if (philo_data->p_round <= philo_data->shared->a_round && get_elapsed_time(philo_data->previous_eat_time) < 50)
		philo_data->can_i_eat = YES;
	else
		philo_data->can_i_eat = NO;
	pthread_mutex_unlock(&philo_data->shared->eating);
	pthread_mutex_lock (&philo_data->shared->print);
	printf(RED "can_i_eat for philo%i is = %i\n"RESET, philo_data->philo_id, philo_data->can_i_eat);
	printf("p_round is for philo%i is:%i, while a_round is:%i\n", philo_data->philo_id, philo_data->p_round, philo_data->shared->a_round);	
	pthread_mutex_unlock (&philo_data->shared->print); //change
}

int	stop_program_check(t_args *philo_data)
{
	int	stop;

	stop = NO;
	pthread_mutex_lock (&philo_data->shared->stop);
	if (philo_data->shared->stop_program == YES)
		stop = YES;
	pthread_mutex_unlock (&philo_data->shared->stop);
	return (stop);
}

int	dead_check(t_args *philo_data)
{
	int		is_dead;
	long	time_passed_since_last_supper;

	is_dead = NO;
	time_passed_since_last_supper = get_elapsed_time(philo_data->previous_eat_time);
	// pthread_mutex_lock (&philo_data->shared->print);
	// printf(RED "time passed = %li\n"RESET, time_passed_since_last_supper);
	// pthread_mutex_unlock (&philo_data->shared->print); //change

	pthread_mutex_lock (&philo_data->shared->death);
	pthread_mutex_lock (&philo_data->shared->stop);
	pthread_mutex_lock (&philo_data->shared->print);
	if (philo_data->shared->is_dead == NO && 
		time_passed_since_last_supper > philo_data->time_to_die)
	{
		philo_data->shared->is_dead = YES;
		philo_data->shared->dead_philo = philo_data->philo_id;
		philo_data->shared->stop_program = YES;
		is_dead = YES;
		death_message(philo_data);
	}
	pthread_mutex_unlock (&philo_data->shared->death);
	pthread_mutex_unlock (&philo_data->shared->stop);
	pthread_mutex_unlock (&philo_data->shared->print);
	return (is_dead);
}

// long	get_elapsed_supper_time(t_args *data)
// {
// 	long	time_passed;

// 	time_passed = get_elapsed_time(data->previous_eat_time);
// 	return (time_passed);
// }
