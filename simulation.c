#include "philo.h"

int initialize_philos(t_program *program)
{
    int i = 0;

    if (!program || !program->philos || program->philos->num_of_philos <= 0)
    {
        fprintf(stderr, "Invalid program structure\n");
        return 0;
    }

    while (i < program->philos->num_of_philos)
    {
        program->philos[i].id = i + 1;
        program->philos[i].eating = 0;
        program->philos[i].meals_eaten = 0;
        program->philos[i].last_meal = 0;
        program->philos[i].start_time = 0;
        program->philos[i].time_to_die = program->philos->time_to_die;
        program->philos[i].time_to_eat = program->philos->time_to_eat;
        program->philos[i].time_to_sleep = program->philos->time_to_sleep;
        program->philos[i].dead = &program->dead_flag;
        program->philos[i].write_lock = &program->write_lock;
        if(program->philos->id % 2 != 0)
        {
            program->philos[i].r_fork = &program->mutex_arr[i];
            program->philos[i].l_fork = &program->mutex_arr[i - 1];
        }
        else
        {
            program->philos[i].r_fork = &program->mutex_arr[i + 1];
            program->philos[i].l_fork = &program->mutex_arr[i];
        }
        program->philos[i].dead_lock = &program->dead_lock;
        program->philos[i].num_times_to_eat = program->philos->num_times_to_eat;
        // program->philos[i].program = program;

        program->philos[i].meal_lock = &program->meal_lock;

        if (!program->philos[i].r_fork || !program->philos[i].l_fork)
        {
            fprintf(stderr, "Failed to allocate memory for mutexes\n");
            while (--i >= 0)
            {
                free(program->philos[i].r_fork);
                free(program->philos[i].l_fork);
            }
            return 0;
        }
        i++;
    }
    return 1;
}

void initialize_mutex(t_program *program)
{
    pthread_mutex_init(&(program->dead_lock), NULL);
    pthread_mutex_init(&program->meal_lock, NULL);
    pthread_mutex_init(&program->write_lock, NULL);
    int i = 0;
    while(i < program->philos->num_of_philos)
    {
        pthread_mutex_init(&(program->mutex_arr[i]), NULL);
        i++;
    }
}

void *philosophers(void *arg)
{
    t_program *program = (t_program *)arg;
    int i = 0;

    if (!program || !program->philos)
    {
        fprintf(stderr, "Invalid program structure\n");
        return NULL;
    }

    while (i < program->philos->num_of_philos)
    {
        if (pthread_create(&program->philos[i].thread, NULL, philosopher_life, &program->philos[i]) != 0)
        {
            fprintf(stderr, "Failed to create thread for philosopher %d\n", i + 1);
            return NULL;
        }
        i++;
    }
    if(pthread_create(&program->monitor_thread, NULL, monitor_routine, program) != 0)
    {
        fprintf(stderr, "Failed to create monitor thread\n");
        program->dead_flag = 1;
        return NULL;
    }
    pthread_join(program->monitor_thread, NULL);
    i = 0;
    while (i < program->philos->num_of_philos)
    {
        pthread_join(program->philos[i].thread, NULL);
        i++;
    }
    return NULL;
}

void *philosopher_life(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if(philo->id % 2 != 0)
    {
        print_status(philo, "is thinking");
        usleep(100);
    }
    int i = 0;
    while (*(!philo->dead))
    {
        eat(philo);
        // if (*(philo->dead))
        //     break;
        sleepp(philo);
    }
    // printf("Philosopher %d has eaten %d times\n", philo->id, philo->meals_eaten);
    return NULL;
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(philo->l_fork);
    print_status(philo, "has taken a fork");
  
    pthread_mutex_lock(philo->meal_lock);
    printf("meal locked\n");
    philo->eating = 1;
    philo->last_meal = get_time();

    pthread_mutex_unlock(philo->meal_lock);
    print_status(philo, "is eating");
    usleep(philo->time_to_eat);
    // smart_sleep(philo->time_to_eat);
    philo->meals_eaten++;
    philo->eating = 0;
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void sleepp(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->time_to_sleep);
}

void print_status(t_philo *philo, char *status)
{
	long long current_time;
	
	pthread_mutex_lock(philo->write_lock);
	current_time = get_time() - philo->start_time;
	if (!philo->eating)
		printf("%lld %d %s\n", current_time, philo->id, status);
	else
		printf("%lld %d %s\n", current_time, philo->id, "is eating");
	pthread_mutex_unlock(philo->write_lock);
}

// void smart_sleep(long long time)
// {
//     long long start;
//     long long now;

//     start = get_time();
//     while (1)
//     {
//         now = get_time();
//         if ((now - start) >= time)
//             break;
//         usleep(500);
//     }
// }

int monitor(t_philo *philo)
{
    long long current_time;
    pthread_mutex_lock(philo->meal_lock);
    current_time = get_time();

    // printf("Philosopher %d: Current time: %lld, Last meal: %zu, Time to die: %zu\n", 
    //    philo->id, current_time, philo->last_meal, philo->time_to_die);

    if ((philo->last_meal != 0) && (current_time - philo->last_meal) > philo->time_to_die)
    {
        pthread_mutex_lock(philo->write_lock);
        printf("%lld %d died\n", current_time, philo->id);
        pthread_mutex_unlock(philo->write_lock);
        *(philo->dead) = 1;
        pthread_mutex_unlock(philo->meal_lock);
        return(1);
    }

    pthread_mutex_unlock(philo->meal_lock);
    return 0;
}


void *monitor_routine(void *arg)
{
    t_program *program = (t_program *)arg;
    int i;

    while (!program->dead_flag)
    {
        i = 0;
        // printf("Monitoring philosophers...\n");
        while (i < program->philos->num_of_philos)
        {
            if (monitor(&program->philos[i]))
            {
                program->dead_flag = 1;
                break;
            }
            i++;
        }
        if (program->dead_flag)
            break;
        usleep(1000);
    }
    return NULL;
}