/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:46:01 by ansoulai          #+#    #+#             */
/*   Updated: 2024/10/16 19:46:06 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_philos(t_program *program)
{
	int	i;

	i = 0;
	if (!program || !program->philos || program->philos->num_of_philos <= 0)
	{
		printf("Invalid program structure\n");
		return (0);
	}
	while (i < program->philos->num_of_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].meals_eaten = 0;
		program->philos[i].start_time = get_time();
		program->philos[i].last_meal = program->philos[i].start_time;
		program->philos[i].time_to_die = program->philos->time_to_die;
		program->philos[i].time_to_eat = program->philos->time_to_eat;
		program->philos[i].time_to_sleep = program->philos->time_to_sleep;
		program->philos[i].dead = &program->dead_flag;
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].full = program->all_eat;
		if (initialize_philos_part2(program, i) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	initialize_philos_part2(t_program *program, int i)
{
	if (program->philos[i].id % 2 != 0)
	{
		program->philos[i].r_fork = &program->mutex_arr[i];
		program->philos[i].l_fork = &program->mutex_arr[(i + 1)
			% program->philos->num_of_philos];
	}
	else
	{
		program->philos[i].r_fork = &program->mutex_arr[(i + 1)
			% program->philos->num_of_philos];
		program->philos[i].l_fork = &program->mutex_arr[i];
	}
	program->philos[i].num_times_to_eat = program->philos->num_times_to_eat;
	program->philos[i].meal_lock = &program->meal_lock;
	return (1);
}

void	initialize_mutex(t_program *program)
{
	int	i;

	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	i = 0;
	while (i < program->philos->num_of_philos)
	{
		pthread_mutex_init(&(program->mutex_arr[i]), NULL);
		i++;
	}
}

void	*philosophers(t_program *program)
{
	int	i;

	i = 0;
	if (!program || !program->philos)
		return (NULL);
	while (i < program->philos->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, philosopher_life,
				&program->philos[i]) != 0)
			return (NULL);
		i++;
	}
	if (pthread_create(&program->monitor_thread, NULL, monitor_routine,
			program) != 0)
		return (NULL);
	pthread_join(program->monitor_thread, NULL);
	i = 0;
	while (i < program->philos->num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	return (NULL);
}

void	*philosopher_life(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		smart_sleep(1);
	while (philo->dead[0] == 0)
	{
		eat(philo);
		if (!philo->full)
			break ;
		sleepp(philo);
		print_status(philo, "is thinking");
		usleep(500);
	}
	return (NULL);
}