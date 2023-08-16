#include "philo.h"
#include <unistd.h>

// Function for philosopher to eat (Solución del Deadlock)
// Para solucionar el problema del deadlock, se puede hacer que los filósofos
// con id par cojan primero el tenedor izquierdo y luego el derecho, mientras
// que los filósofos con id impar cojan primero el tenedor derecho y luego el
// izquierdo. De esta forma, si todos los filósofos cogen el tenedor izquierdo
// al mismo tiempo, ninguno de ellos podrá coger el tenedor derecho, pero si
// todos los filósofos cogen el tenedor derecho al mismo tiempo, todos podrán
// coger el tenedor izquierdo.
void eat(t_philosopher *philosopher)
{
    if (philosopher->id % 2 == 0)
    {
        pthread_mutex_lock(philosopher->left_fork);
        print_status(philosopher, "has taken a fork");
        pthread_mutex_lock(philosopher->right_fork);
    }
    else
    {
        pthread_mutex_lock(philosopher->right_fork);
        print_status(philosopher, "has taken a fork");
        pthread_mutex_lock(philosopher->left_fork);
    }
    print_status(philosopher, "has taken a fork");

    philosopher->is_eating = true;
    philosopher->last_eat_time = get_time_in_ms();
    print_status(philosopher, "is eating");
    usleep(philosopher->time_to_eat * 1000);

    // Incrementar el contador de veces que el filósofo ha comido (AÑADIDO)
    philosopher->times_eaten++;
    
    // Verificar si el filósofo ha comido suficiente (AÑADIDO)
    if (philosopher->must_eat_count_is_set && philosopher->times_eaten >= philosopher->times_must_eat)
    {
        print_status(philosopher, "has eaten enough and is leaving the table");
        pthread_exit(NULL);
    }

    philosopher->is_eating = false;
    pthread_mutex_unlock(philosopher->left_fork);
    pthread_mutex_unlock(philosopher->right_fork);
    print_status(philosopher, "is sleeping");
}

// Function for philosopher to sleep and think
void sleep_and_think(t_philosopher *philosopher)
{
    usleep(philosopher->time_to_sleep * 1000);
    print_status(philosopher, "is thinking");
}

// Main function for philosopher's life
void *philosopher_life(void *philosopher_ptr)
{
    t_philosopher *philosopher = (t_philosopher *)philosopher_ptr;

    while (true)
    {
        eat(philosopher);
        sleep_and_think(philosopher);
    }

    return NULL;
}