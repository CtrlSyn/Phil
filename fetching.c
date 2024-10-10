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


// void initialize_mutex(t_program *program)
// {
// 	pthread_mutex_init(&program->dead_lock, NULL);
// 	pthread_mutex_init(&program->meal_lock, NULL);
// 	pthread_mutex_init(&program->write_lock, NULL);
// }
// int initialize_philos(t_program *program)
// {
//     int i = 0;
    
//     if (!program || !program->philos)
//     {
//         fprintf(stderr, "Invalid program structure\n");
//         return 0;
//     }

//     while (i < program->philos->num_of_philos)  
//     {
//         program->philos[i].id = i + 1;  
//         program->philos[i].eating = 0;
//         program->philos[i].meals_eaten = 0;
//         program->philos[i].last_meal = 0;
//         program->philos[i].start_time = 0;
//         program->philos[i].dead = &program->dead_flag;
        
//         program->philos[i].r_fork = malloc(sizeof(pthread_mutex_t));
//         program->philos[i].l_fork = malloc(sizeof(pthread_mutex_t));
        
//         if (!program->philos[i].r_fork || !program->philos[i].l_fork)
//         {
//             fprintf(stderr, "Failed to allocate memory for mutexes\n");
//             while (--i >= 0)
//             {
//                 free(program->philos[i].r_fork);
//                 free(program->philos[i].l_fork);
//             }
//             return 0;
//         }
        
//         if (pthread_mutex_init(program->philos[i].r_fork, NULL) != 0 ||
//             pthread_mutex_init(program->philos[i].l_fork, NULL) != 0)
//         {
//             fprintf(stderr, "Failed to initialize mutexes\n");
//             free(program->philos[i].r_fork);
//             free(program->philos[i].l_fork);
//             while (--i >= 0)
//             {
//                 pthread_mutex_destroy(program->philos[i].r_fork);
//                 pthread_mutex_destroy(program->philos[i].l_fork);
//                 free(program->philos[i].r_fork);
//                 free(program->philos[i].l_fork);
//             }
//             return 0;  
//         }
        
//         program->philos[i].write_lock = &program->write_lock;
//         program->philos[i].dead_lock = &program->dead_lock;
//         program->philos[i].meal_lock = &program->meal_lock;
        
//         i++;
//     }
    
//     return 1;  
// }

int get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
