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

static int	wait_exit(t_shared *shared)
{
	int	exit_program;

	exit_program = NO;
	pthread_mutex_lock(&shared->stop);
	if (shared->stop_program == shared->n_philo)
		exit_program = YES;
	pthread_mutex_unlock(&shared->stop);
	return (exit_program);
}

void	exit_delay(t_args *philo_data)
{
	pthread_mutex_lock(&philo_data->shared->stop);
	philo_data->shared->stop_program += 1;
	pthread_mutex_unlock(&philo_data->shared->stop);
	while (wait_exit(philo_data->shared) == NO)
		usleep(100);
}

void	ft_routine_time(t_args *philo_data, long routine_time)
{
	long	start;

	start = get_time();
	while ((dead_check(philo_data) == NO)
		&& (get_time() - start) < routine_time)
	{
		usleep(100);
	}
}

void	set_turn(t_args *philo_data)
{
	pthread_mutex_lock(&philo_data->shared->eating);
	philo_data->shared->turn += 1;
	if (philo_data->shared->turn == philo_data->shared->n_philo + 1)
		philo_data->shared->turn = 1;
	pthread_mutex_unlock(&philo_data->shared->eating);
}

void	set_position(t_args *philo_data)
{
	if (philo_data->set_position == YES)
	{
		pthread_mutex_lock(&philo_data->shared->eating);
		philo_data->position = philo_data->shared->turn;
		pthread_mutex_unlock(&philo_data->shared->eating);
		philo_data ->set_position = NO;
	}
}
