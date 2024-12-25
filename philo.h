/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:13:44 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/12/21 18:30:28 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//****************/*LIBRARIES*/********************//
# include <pthread.h>
# include <printf.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h> 
# include <sys/time.h>

//****************/*MACRO*/********************//
# define EXIT_ERROR_ARGS -1
# define EXIT_ERROR_THREAD -2
# define EXIT_ERROR_TOO_FEW_PHILOSOPHERS -3
# define EXIT_ERROR_STRUCT_INIT -4
# define EXIT_ERROR_DEATH -6

# define RED   "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"
# define YELLOW "\033[1;33m"
# define ORANGE "\033[0;33m"
# define BLU "\033[0;34m"

# define YES 0
# define NO 1

# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DEATH 5
# define FORK 6
//****************/*STRUCTURES*/********************//
struct	s_args;

//***Program arg struct***//
typedef struct s_shared
{
	pthread_mutex_t	print;
	pthread_mutex_t	stop;
	pthread_mutex_t	death;
	pthread_mutex_t	eating;
	struct s_args	*philo_data;
	int				n_philo;
	int				is_dead;
	int				stop_program;
	int				stop_printing;
	int				turn;
}		t_shared;

//***Single philo struct***//
typedef struct s_args
{
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_id;
	long			start_time;
	long			previous_eat_time;
	int				set_position;
	int				position;
	int				meals;
	int				dead;
	int				stop;
	t_shared		*shared;
}				t_args;

//****************/*FUNCTIONS*/********************//
//***Error checks***//
void	ft_exit_error(int error_type);
void	ft_error_check(int argc, char **argv);

//***Utils***//
int		ft_atoi(char *digit);
void	print_message(t_args *philo_data, int n);
void	death_message(t_args *philo_data);
void	print_one_death(t_args *data, t_shared *shared);

//***Time checks***//
long	get_elapsed_time(long relation_time);
long	get_time(void);
int		dead_check(t_args *philo_data);
int		check_if_i_can_eat(t_args *philo_data);
int		check_termination(t_args *philo_data);

//***Struct initialization***//
void	arg_data_init(t_args *data, t_shared *shared, char **argv);
void	ft_destroy_mutexes(t_args *philo_data, t_shared *shared);

//***Thread management***//
int		ft_join_threads(pthread_t *philo, t_args *philo_data);
void	ft_threads(t_args *data, t_shared *shared);

//***Routines***//
void	*routine(void *arg);
void	ft_routine_time(t_args *philo_data, long routine_time);
void	exit_delay(t_args *philo_data);
void	set_turn(t_args *philo_data);
void	set_position(t_args *philo_data);

#endif