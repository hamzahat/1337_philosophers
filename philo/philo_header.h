#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>

typedef struct s_table
{
    pthread_mutex_t *forks;
    t_philos    *philos_arr;
    int philo_nb;
}   t_table;

typedef struct s_philos
{
    int id;

}   t_philos;


#endif
