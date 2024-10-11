#include "philo.h"

void input_error(void)
{
	printf("Error : Wrong number of arguments\n");
	exit(1);
}
void input_into_struct(t_program *program, char **av)
{
	program->philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	program->dead_flag = 0;
	program->philos->num_of_philos = ft_atoi(av[1]);
	program->philos->time_to_die = ft_atoi(av[2]);
	program->philos->time_to_eat = ft_atoi(av[3]);
	program->philos->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		program->philos->num_times_to_eat = ft_atoi(av[5]);
	else
		program->philos->num_times_to_eat = -1;
	program->mutex_arr = malloc(sizeof(pthread_mutex_t) * program->philos->num_of_philos);
}

int get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
