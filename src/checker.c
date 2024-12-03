/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:06:46 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/11/30 19:51:23 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	terminate_prog(t_shared *shared)
{
	pthread_mutex_lock(&shared->stop);
	shared->stop_program = YES;
	pthread_mutex_unlock(&shared->stop);
	pthread_mutex_lock(&shared->print);
	shared->stop_printing = YES;
	pthread_mutex_unlock(&shared->print);
	pthread_mutex_unlock(&shared->eating);
	pthread_mutex_unlock(&shared->death);
}

void	*checker(void *shared_struct)
{
	int			n;
	t_shared	*shared;

	shared = (t_shared *)shared_struct;
	while (1)
	{
		pthread_mutex_lock(&shared->death);
		pthread_mutex_lock(&shared->eating);
		n = shared->n_philo * shared->boundmeals;
		if (shared->is_dead == YES || 
			(shared->boundmeals > 0 && shared->ntime_eating >= n))
		{
			terminate_prog(shared);
			break ;
		}
		if (shared->ntime_eating % shared->n_philo == 0)
			shared->a_round += 1;
		pthread_mutex_unlock(&shared->eating);
		pthread_mutex_unlock(&shared->death);
	}
	return (NULL);
}
