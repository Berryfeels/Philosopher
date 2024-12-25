/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:58:22 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/21 18:51:22 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_message(t_args *philo_data, int n)
{
	long	elapsed_time;

	pthread_mutex_lock (&philo_data->shared->print);
	elapsed_time = get_elapsed_time(philo_data-> start_time);
	if (philo_data->shared->stop_printing == NO)
	{
		printf("%li %i ", elapsed_time, philo_data->philo_id);
		if (n == EATING)
		{
			printf(GREEN"is eating\n"RESET);
		}
		if (n == SLEEPING)
			printf(BLU"is sleeping\n"RESET);
		if (n == THINKING)
			printf(YELLOW"is thinking\n"RESET);
		if (n == FORK)
			printf("has taken a fork\n");
	}
	pthread_mutex_unlock(&philo_data->shared->print);
}

void	death_message(t_args *philo_data)
{
	long	elapsed_time;

	pthread_mutex_lock (&philo_data->shared->print);
	if (philo_data->shared->stop_printing == NO)
	{
		elapsed_time = get_elapsed_time(philo_data-> start_time);
		printf("%li %i ", elapsed_time, philo_data->philo_id);
		printf(RED"died\n"RESET);
		philo_data->shared->stop_printing = YES;
	}
	pthread_mutex_unlock (&philo_data->shared->print);
}
