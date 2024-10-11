/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:31:25 by ansoulai          #+#    #+#             */
/*   Updated: 2024/10/11 10:18:35 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <malloc.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
#include  <time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	// t_program		*program;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	pthread_t 		monitor_thread;
	pthread_mutex_t	*mutex_arr;
}					t_program;

// Parsing functions : 

int ft_strlen(char *str);
int is_valid_str(char *str);
int ft_atoi(char *str);

// Fetching functions :
void input_into_struct(t_program *program, char **av);
void print_struct(t_program *program);
void input_error(void);
int initialize_philos(t_program *program);
void initialize_mutex(t_program *program);
int get_time(void);

// Simulation functions :
int initialize_philos(t_program *program);
void *philosopher_life(void *arg);
void *philosophers(void *arg);
void eat(t_philo *philo);
void sleepp(t_philo *philo);
void print_status(t_philo *philo, char *status);
void smart_sleep(long long time);
int monitor(t_philo *philo);
void *monitor_routine(void *arg);


#endif
