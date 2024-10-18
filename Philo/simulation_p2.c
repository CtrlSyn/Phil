/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peaky <peaky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:45:51 by ansoulai          #+#    #+#             */
/*   Updated: 2024/10/18 01:53:51 by peaky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return ;
	print_status(philo, "has taken a fork");
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
	long long	current_time;

	pthread_mutex_lock(philo->write_lock);
	current_time = get_time() - philo->start_time;
	if (philo->dead[0] == 0)
		printf("%lld %d %s\n", current_time, philo->id, status);
	pthread_mutex_unlock(philo->write_lock);
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
