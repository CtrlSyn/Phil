/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:45:37 by ansoulai          #+#    #+#             */
/*   Updated: 2024/10/20 23:40:42 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor(t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(philo->meal_lock);
	current_time = get_time();
	if ((current_time - philo->last_meal) > philo->time_to_die)
	{
		pthread_mutex_lock(philo->dead_flag_mutex);
		if (*(philo->dead) == 0)
		{
			*(philo->dead) = 1;
			pthread_mutex_lock(philo->write_lock);
			printf("%lld %d died\n", (current_time - philo->start_time),
				philo->id);
			pthread_mutex_unlock(philo->write_lock);
		}
		pthread_mutex_unlock(philo->dead_flag_mutex);
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	kolchi_kla(t_program *program)
{
	int	i;

	i = program->philos->num_of_philos - 1;
	if (program->philos[i].num_times_to_eat == -1)
		return (0);
	while (i >= 0)
	{
		pthread_mutex_lock(&program->meal_lock);
		if ((program->philos[i].meals_eaten
				< program->philos[i].num_times_to_eat))
		{
			pthread_mutex_unlock(&program->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&program->meal_lock);
		i--;
	}
	program->all_eat = 1;
	program->philos->dead[0] = 1;
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;
	int			i;

	program = (t_program *)arg;
	while (!program->dead_flag)
	{
		i = 0;
		while (i < program->philos->num_of_philos)
		{
			if (monitor(&program->philos[i]))
				break ;
			i++;
		}
		kolchi_kla(program);
	}
	return (NULL);
}
