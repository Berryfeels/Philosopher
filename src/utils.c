/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:15:08 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/10/26 00:07:44 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *digit)
{
	int num;

	if (digit[0]< '0' || digit [0] > '9')
		ft_exit_error(EXIT_ERROR_ARGS);
	num = 0;
	while (*digit)
	{
		num = (num * 10) + (*digit - 48); 
		digit++;
	} 
	return (num); 
}
