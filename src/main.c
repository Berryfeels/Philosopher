/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:07:06 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/04 13:48:57 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_args		*data;
	t_shared	*shared;

	ft_error_check(argc, argv);
	shared = (t_shared *)malloc(sizeof(t_shared));
	if (!shared)
	{
		ft_exit_error(EXIT_ERROR_STRUCT_INIT);
		exit(EXIT_FAILURE);
	}
	data = (t_args *)malloc(sizeof(t_args));
	if (!data)
	{
		ft_exit_error(EXIT_ERROR_STRUCT_INIT);
		exit(EXIT_FAILURE);
	}
	arg_data_init (data, shared, argv);
	ft_threads(data, shared);
	free(shared);
	return (0);
}
