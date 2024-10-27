/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:13:44 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/10/26 00:02:32 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHILO_H
# define LIBPHILO_H

//****************/*LIBRARIES*/********************//
#include <pthread.h>
#include <printf.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/time.h>


//****************/*MACRO*/********************//
#define EXIT_ERROR_ARGS -1
#define EXIT_ERROR_THREAD -2
#define EXIT_ERROR_TOO_FEW_PHILOSOPHERS -3
#define EXIT_ERROR_STRUCT_INIT -4
#define EXIT_ERROR_DEATH -6

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

#define YES 0
#define NO 1

//****************/*STRUCTURES*/********************//

//***Single philo struct***//
typedef struct s_shared
{
	pthread_mutex_t fork[200];
	int dead_philo;
	int is_dead;
	int stop_program;
	pthread_mutex_t death_mutex;
}		t_shared;

//***Program arg struct***//
typedef struct	s_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	int philo_id;
	long start_time;
	long previous_eat_time;
	t_shared *shared;
	int fork_right;
	int fork_left;
	
}				t_args;


//****************/*FUNCTIONS*/********************//
//***Error checks***//
void	ft_exit_error(int error_type);
void ft_error_check(int argc, char **argv);

//***Utils***//
int	ft_atoi(char *digit);

//***Time checks***//
long get_elapsed_time(long relation_time);
int stop_program_check(t_args *philo_data);
long get_time();
void *supervising(void *shared);
void is_philo_dead_check(t_args *philo_data);
long get_elapsed_supper_time(t_args *data);

//***Struct initialization***//
void arg_data_init (t_args *data, t_shared *shared, char **argv);

//***Thread management***//
int	ft_join_threads(pthread_t *philo, t_args *data);
void	ft_threads(t_args *data);

//***Routines***//
void *routine_even(void *arg);

void *routine_odd(void *arg);
# endif