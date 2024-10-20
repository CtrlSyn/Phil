/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:45:51 by ansoulai          #+#    #+#             */
/*   Updated: 2024/10/20 23:40:11 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return ;
	print_status(philo, "has taken a fork");
	if (philo->num_of_philos == 1)
	{
		smart_sleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	if (pthread_mutex_lock(philo->l_fork) != 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	smart_sleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten = philo->meals_eaten + 1;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleepp(t_philo *philo)
{
	print_status(philo, "is sleeping");
	smart_sleep(philo->time_to_sleep);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->dead_flag_mutex);
	if (*(philo->dead) == 0)
	{
		pthread_mutex_lock(philo->write_lock);
		printf("%lld %d %s\n", get_time() - philo->start_time, philo->id,
			status);
		pthread_mutex_unlock(philo->write_lock);
	}
	pthread_mutex_unlock(philo->dead_flag_mutex);
}

void	smart_sleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		usleep(100);
	}
}
