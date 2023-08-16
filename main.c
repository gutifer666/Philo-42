#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

// Function to initialize the simulation
bool initialize_simulation(t_simulation *simulation)
{
    simulation->forks = malloc(simulation->number_of_philosophers * sizeof(pthread_mutex_t));
    for (int i = 0; i < simulation->number_of_philosophers; i++)
    {
        pthread_mutex_init(&simulation->forks[i], NULL);
        simulation->philosophers[i].left_fork = &simulation->forks[i];
        simulation->philosophers[i].right_fork = &simulation->forks[(i + 1) % simulation->number_of_philosophers];
        pthread_mutex_init(&simulation->philosophers[i].eat_mutex, NULL);
    }
    pthread_mutex_init(&simulation->print_mutex, NULL);
    simulation->start_time = get_time_in_ms();
    return true;
}

// Function to start the simulation
void start_simulation(t_simulation *simulation)
{
    for (int i = 0; i < simulation->number_of_philosophers; i++)
    {
        pthread_create(&simulation->philosophers[i].thread, NULL, philosopher_life, &simulation->philosophers[i]);
    }

    for (int i = 0; i < simulation->number_of_philosophers; i++)
    {
        pthread_join(simulation->philosophers[i].thread, NULL);
    }
}

// Main function
int main(int argc, char **argv)
{
    t_simulation simulation;

    if (!parse_arguments(argc, argv, &simulation) || !initialize_simulation(&simulation))
    {
        return EXIT_FAILURE;
    }

    start_simulation(&simulation);

    // Free resources
    free(simulation.philosophers);
    free(simulation.forks);
    return EXIT_SUCCESS;
}