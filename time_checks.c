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

int	check_if_i_can_eat(t_args *philo_data)
{
	int	can_i;

	can_i = NO;
	pthread_mutex_lock(&philo_data->shared->eating);
	if (philo_data->position == philo_data->shared->turn)
		can_i = YES;
	pthread_mutex_unlock(&philo_data->shared->eating);
	return (can_i);
}

int	check_termination(t_args *philo_data)
{
	pthread_mutex_lock(&philo_data->shared->death);
	if (philo_data->shared->is_dead > 0)
		philo_data->stop = YES;
	pthread_mutex_unlock(&philo_data->shared->death);
	return (philo_data->stop);
}

int	dead_check(t_args *philo_data)
{
	int	last_supper_time;

	last_supper_time = get_elapsed_time(philo_data->previous_eat_time);
	if (last_supper_time > philo_data->time_to_die)
	{
		pthread_mutex_lock(&philo_data->shared->death);
		philo_data->shared->is_dead += 1;
		pthread_mutex_unlock(&philo_data->shared->death);
		philo_data->dead = YES;
	}
	return (philo_data->dead);
}
