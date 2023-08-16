#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

// Function to get the current time in milliseconds
long long get_time_in_ms()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000LL) + (time.tv_usec / 1000);
}

// Function to print the status of a philosopher
void print_status(t_philosopher *philosopher, const char *status)
{
    pthread_mutex_lock(&philosopher->eat_mutex);
    printf("%lld %d %s\n", get_time_in_ms() - philosopher->last_eat_time, philosopher->id, status);
    pthread_mutex_unlock(&philosopher->eat_mutex);
}

// Function to parse the command-line arguments
bool parse_arguments(int argc, char **argv, t_simulation *simulation)
{
    if (argc < 5 || argc > 6)
    {
        fprintf(stderr, "Error: Wrong number of arguments!\n");
        return false;
    }

    simulation->number_of_philosophers = atoi(argv[1]);
    int time_to_die = atoi(argv[2]);
    int time_to_eat = atoi(argv[3]);
    int time_to_sleep = atoi(argv[4]);
    int times_must_eat = (argc == 6) ? atoi(argv[5]) : -1;

    // Validation
    if (simulation->number_of_philosophers <= 0 || time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0 || (argc == 6 && times_must_eat <= 0))
    {
        fprintf(stderr, "Error: Invalid arguments!\n");
        return false;
    }

    // Initialization of philosophers
    simulation->philosophers = malloc(simulation->number_of_philosophers * sizeof(t_philosopher));
    for (int i = 0; i < simulation->number_of_philosophers; i++)
    {
        simulation->philosophers[i].id = i + 1;
        simulation->philosophers[i].time_to_die = time_to_die;
        simulation->philosophers[i].time_to_eat = time_to_eat;
        simulation->philosophers[i].time_to_sleep = time_to_sleep;
        simulation->philosophers[i].times_eaten = 0; // AÑADIDO
        simulation->philosophers[i].must_eat_count_is_set = (argc == 6); // AÑADIDO
        simulation->philosophers[i].times_must_eat = times_must_eat;
    }

    return true;
}