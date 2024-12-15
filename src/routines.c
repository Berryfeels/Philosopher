/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:06:46 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/15 21:17:07 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	sleeping_routine(t_args *philo_data)
{
	print_message(philo_data, SLEEPING);
	ft_routine_time(philo_data, philo_data->time_to_sleep);
	// pthread_mutex_lock (&philo_data->shared->print);
	// printf(RED "time passed = %li\n"RESET, get_elapsed_time(philo_data->previous_eat_time));
	// pthread_mutex_unlock (&philo_data->shared->print); //change
	
}

void	eating_routine(t_args *philo_data)
{
	philo_data->p_round += 1;
	//check_if_i_can_eat(philo_data);
	
	//if (philo_data->can_i_eat == YES)
	//{
		if (philo_data->philo_id % 2 == 0)
		{
			pthread_mutex_lock(&philo_data->l_fork);
			pthread_mutex_lock(philo_data->r_fork);
			print_message(philo_data, FORK);
		}
		else
		{
			pthread_mutex_lock(philo_data->r_fork);
			pthread_mutex_lock(&philo_data->l_fork);
			print_message(philo_data, FORK);
		}
		dead_check(philo_data);
		pthread_mutex_lock(&philo_data->shared->eating);
		philo_data->shared->ntime_eating += 1;
		pthread_mutex_unlock(&philo_data->shared->eating);
		print_message(philo_data, EATING);
		philo_data->previous_eat_time = get_time();
		ft_routine_time(philo_data, philo_data->time_to_eat);
		pthread_mutex_unlock(&philo_data->l_fork);
		pthread_mutex_unlock(philo_data->r_fork);
	//}
	// pthread_mutex_lock (&philo_data->shared->print);
	// printf(RED "time passed = %li\n"RESET, get_elapsed_time(philo_data->previous_eat_time));
	// pthread_mutex_unlock (&philo_data->shared->print); //change

}

void	thinking_routine(t_args *philo_data)
{
	//long think_time;

	//int philo_num = philo_data->shared->n_philo;
	print_message(philo_data, THINKING);
		
	// if(philo_num % 2 == 0)
	// {
	// 	think_time = philo_data->time_to_eat + 5;
		
	// 	ft_routine_time(philo_data, think_time);

	// 	//////////////////
	// 	pthread_mutex_lock (&philo_data->shared->print);
	// 	printf(RED "time passed thinking for %i= %li\n"RESET, philo_data->philo_id, get_elapsed_time(philo_data->previous_eat_time));
	// 	pthread_mutex_unlock (&philo_data->shared->print); //change
	// 	//////////////////	

	// }
	// else if(philo_num % 2 != 0)
	// {		
	// 	think_time = philo_data->time_to_die - 
	// 					(philo_data->time_to_eat + philo_data->time_to_sleep);
	// 	ft_routine_time(philo_data, think_time);
	// 	/////////////////
	// 	pthread_mutex_lock (&philo_data->shared->print);
	// 	printf(RED "Time passed thinking for %i= %li\n"RESET, philo_data->philo_id, get_elapsed_time(philo_data->previous_eat_time));
	// 	pthread_mutex_unlock (&philo_data->shared->print); //change
	// 	/////////////////
	// }
	while(philo_data->can_i_eat == NO)
	{
		if(philo_data->shared->is_dead != 0)
			break;
		dead_check(philo_data);
		check_if_i_can_eat(philo_data);
	}
}

void	*routine(void *arg)
{
	t_args	*philo_data;

	philo_data = (t_args *) arg;
	if (philo_data->philo_id % 2 == 0)
		usleep(10000); //changed
	while (1)
	{
		eating_routine(philo_data);
		if (stop_program_check(philo_data) == YES)
			break ;
		sleeping_routine(philo_data);
		if (stop_program_check(philo_data) == YES)
			break ;
		thinking_routine(philo_data);
		if (stop_program_check(philo_data) == YES)
			break ;
	}
	return (NULL);
}
