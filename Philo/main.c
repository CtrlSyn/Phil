/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:45:25 by ansoulai          #+#    #+#             */
/*   Updated: 2024/10/16 19:45:28 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_program	program;
	int			i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Error : Wrong number of arguments\n");
		return (1);
	}
	while (av[i])
	{
		if (!is_valid_str(av[i]) || ft_atoi(av[i]) <= 0 || ft_atoi(av[1]) > 200)
		{
			printf("Error : argument\n");
			return (0);
		}
		i++;
	}
	input_into_struct(&program, av);
	initialize_philos(&program);
	initialize_mutex(&program);
	philosophers(&program);
	cleanup_resources(&program);
	return (1);
}
