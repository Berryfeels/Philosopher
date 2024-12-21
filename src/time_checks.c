/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:09:26 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/21 18:08:28 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_if_i_can_eat(t_args *philo_data)
{
	if(get_elapsed_time(philo_data->previous_eat_time) > philo_data->time_to_sleep)
	{
		philo_data->can_i_eat = YES;
	}
	else
	{
		philo_data->can_i_eat = NO;
	}
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
	int	time_passed_since_last_supper;

	time_passed_since_last_supper = get_elapsed_time(philo_data->previous_eat_time);
	if (time_passed_since_last_supper > philo_data->time_to_die)
	{
		pthread_mutex_lock(&philo_data->shared->death);
		philo_data->shared->is_dead = YES;
		pthread_mutex_unlock(&philo_data->shared->death);
		philo_data->dead = YES;
	}
	return (philo_data->dead);
}

