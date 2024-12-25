/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:15:08 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/04 13:48:48 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *digit)
{
	int	i;
	int	num;

	i = 0;
	while (digit[i])
	{
		if (digit [i] < '0' || digit [i++] > '9')
			ft_exit_error(EXIT_ERROR_ARGS);
	}
	num = 0;
	while (*digit)
	{
		num = (num * 10) + (*digit - 48);
		digit++;
	}
	return (num);
}

long	get_elapsed_time(long relation_time)
{
	long	now;
	long	elapsed_time;

	now = get_time();
	elapsed_time = now - relation_time;
	return (elapsed_time);
}

long	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000L) + (current.tv_usec / 1000L));
}
