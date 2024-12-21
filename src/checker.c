/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:06:46 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/21 18:29:44 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_termination(t_shared *shared)
{
	pthread_mutex_lock(&shared->death);
	if ((shared->is_dead) == YES)
		return(YES);
	pthread_mutex_unlock(&shared->death);
	return (NO);
}

// void unlock_forks_on_death(t_args *philo_data)
// {
//     pthread_mutex_unlock(&philo_data->l_fork);
//     pthread_mutex_unlock(philo_data->r_fork);
// }

// void unlock_forks(t_shared *shared, t_args *philo_data)
// {
// 	int i = 0;
//     while (i < shared->n_philo)
//     {
//         if (philo_data[i].philo_id == shared->dead_philo)
//             unlock_forks_on_death(&philo_data[i]);
//         i++;
//     }
// }
	
//void	*checker(void *shared_struct)
//{
	///t_shared	*shared;
	//int flag;
	//int temp;
//	int tot_meals = 0;
	
	//shared = (t_shared *)shared_struct;
	//flag = NO;
	//temp = 0;
	//while (1)
	//{
		
		// pthread_mutex_lock(&shared->eating);
		// tot_meals = shared->ntime_eating;
		// pthread_mutex_unlock(&shared->eating);
		// if ((check_termination(shared) == YES) ||(shared->boundmeals * shared->n_philo == tot_meals))
		// 	break ;
		// pthread_mutex_lock (&shared->print);
		// printf("death_check: %i\n", check_termination(shared));
		// pthread_mutex_unlock (&shared->print);
//		break;
//	}
//	return (NULL);
//}
