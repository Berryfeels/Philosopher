/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:58:22 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/21 18:48:33 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_one_death(t_args *data, t_shared *t_shared)
{
	usleep((data->time_to_die + 1) * 1000);
	printf("%i 1 ", data->time_to_die + 1);
	printf(RED"died\n"RESET);
	free(data);
	free(t_shared);
	exit(EXIT_SUCCESS);
}

void	ft_exit_error(int error_type)
{
	if (error_type == EXIT_ERROR_ARGS)
		printf("args must be 4 or 5, != 0 and only numbers\n");
	if (error_type == EXIT_ERROR_THREAD)
		printf("Thread initialization issue\n");
	if (error_type == EXIT_ERROR_TOO_FEW_PHILOSOPHERS)
		printf("Not enough philosophers\n");
	if (error_type == EXIT_ERROR_STRUCT_INIT)
		printf("Structure initialization issue\n");
	exit (EXIT_FAILURE);
}

void	ft_error_check(int argc, char **argv)
{
	int	i;
	int	n_philo;

	if (argc < 5 || argc > 6)
		ft_exit_error(EXIT_ERROR_ARGS);
	i = 1;
	while (i < argc)
	{
		if (argv[i++][0] == '0')
			ft_exit_error(EXIT_ERROR_ARGS);
	}
	n_philo = ft_atoi(argv[1]);
	if (n_philo < 1)
		ft_exit_error(EXIT_ERROR_ARGS);
}
