#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_table
{
    pthread_mutex_t *forks;
    t_philos    *philos_arr;
    int philo_nb;
}   t_table;

typedef struct s_philo
{
    int philo_id;
	// *left_fork
	// *right_fork
	int	nb_meals;

}   t_philo;


#endif
