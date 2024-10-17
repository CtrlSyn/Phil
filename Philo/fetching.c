/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:45:15 by ansoulai          #+#    #+#             */
/*   Updated: 2024/10/16 19:45:19 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	input_error(void)
{
	printf("Error : Wrong number of arguments\n");
	exit(1);
}

void	input_into_struct(t_program *program, char **av)
{
	program->philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	program->philos->num_of_philos = ft_atoi(av[1]);
	program->dead_flag = 0;
	program->philos->time_to_die = ft_atoi(av[2]);
	program->philos->time_to_eat = ft_atoi(av[3]);
	program->philos->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		program->philos->num_times_to_eat = ft_atoi(av[5]);
	else
		program->philos->num_times_to_eat = -1;
	program->mutex_arr = malloc(sizeof(pthread_mutex_t)
			* program->philos->num_of_philos);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	cleanup_resources(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philos->num_of_philos)
	{
		pthread_mutex_destroy(&program->mutex_arr[i]);
		i++;
	}
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
	free(program->philos);
	free(program->mutex_arr);
}
