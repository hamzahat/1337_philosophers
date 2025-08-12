/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:44:29 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/12 10:34:48 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

//* * * Macros for ft_safe_malloc keys * * *//

# define ALLOCATE 1
# define FREE_ALL 0
# define FREE_ONE 2

//* * * Headers * * *//

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>

//* * * Philo routine messages * * *//

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIE "died"

//* * * Structures * * *//

typedef struct s_table t_table;

//? ft_safe_malloc struct:
typedef struct s_mem_node
{
	void				*address;
	struct s_mem_node	*next;
}						t_mem_node;

//? philo's struct:
typedef struct s_philo
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	long			last_meal_time;
	int				meals_counter;
	int				philo_id;
	bool			philo_is_full;
	pthread_t		thread_id;
	t_table			*table;
}					t_philo;

//? table struct:
struct s_table
{
	t_philo			*philos_arr;
	pthread_mutex_t	*forks_arr;
	pthread_t		monitor;
	int				philos_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_nbr;
	long			start_simulation_time;
	bool			end_simulation;
	pthread_mutex_t	end_simu_mtx;
	pthread_mutex_t	write_lock_mtx;
	//todo: add mutexs
};

//* * * Functions prototypes * * *//



#endif
