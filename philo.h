#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

// Structure to represent a philosopher
typedef struct s_philosopher
{
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int times_must_eat;
    int times_eaten; // Number of times the philosopher has eaten (AÑADIDO)
    bool must_eat_count_is_set; // Flag to indicate if the must_eat_count has been set (AÑADIDO)
    long long last_eat_time;
    bool is_eating;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t eat_mutex;
}               t_philosopher;

// Structure to represent the simulation
typedef struct s_simulation
{
    int number_of_philosophers;
    t_philosopher *philosophers;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    long long start_time;
}               t_simulation;

// Function declarations
void *philosopher_life(void *philosopher_ptr);
void eat(t_philosopher *philosopher);
void sleep_and_think(t_philosopher *philosopher);
bool parse_arguments(int argc, char **argv, t_simulation *simulation);
long long get_time_in_ms();
void print_status(t_philosopher *philosopher, const char *status);

#endif