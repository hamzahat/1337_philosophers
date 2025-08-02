/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:35:19 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/02 07:59:03 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

//* * * Macros for ft_safe_malloc keys:
# define ALLOCATE 1
# define FREE_ALL 0
# define FREE_ONE 2

//* * * headers * * *//

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

//* * * structures * * *//

typedef struct s_table t_table;

//? ft_saf_malloc struct:
typedef struct s_mem_node
{
	void				*address;
	struct s_mem_node	*next;
}						t_mem_node;

typedef struct s_fork
{
	pthread_mutex_t	fork;		//? (mutex) fork
	int				fork_id;	//? fork id
}	t_fork;

typedef struct s_philo
{
	t_fork			*second_fork;		//? ptr to t_fork (mutex) left fork
	t_fork			*first_fork;		//? ptr to t_fork (mutex) right fork
	long			last_meal_time;		//? the last meal time
	int				philo_id;			//? philo id
	int				meals_counter;		//? meals eaten number
	bool			meals_full;			//? boolian => if the philo eat all the meals = 1
	pthread_t		thread_id;			//? philo is thread id
	t_table			*table;				//? ptr to table contents (I don't know i will need it or now)
}	t_philo;

struct s_table
{
	t_philo			*philos_arr;	//? ptr to an array of philos ( t_philo struct )
	t_fork			*forks_arr;		//? ptr to an array of forks ( mutex )
	int				philo_nb;		//? number of philos ( from argv )
	int				time_to_die;	//? time to die in ms
	int				time_to_eat;	//? time to eat in ms
	int				time_to_sleep;	//? time to sleep in ms
	int				meals_nb;		//? number of meals every philo should eat!
	long			start_simulation;//? the start time of simulation
	bool			end_simulation; //? a philo die or all philos full (falg 1/0)
};


//* * * functions prototypes * * *//

//? --- parsing functions ---

int		parse_intput(int ac, char *av[], t_table *table);
void	ft_putstr_fd(int fd, char *str);
size_t	ft_strlen(char *str);
int		ft_atoi(char *str);
void	printf_input_data(t_table table);

//? --- data initialization ---

int	philos_init(t_table *table);
int	forks_init(t_table *table);

//? --- garbage collector functions ---

void	*ft_safe_malloc(size_t size, int key, void *to_delete);
int		allocate_philos_arr(t_table *table);
int		allocate_forks_arr(t_table *table);

#endif

/*
* * * structs & typedefs size:
pthread_t       => 72 bytes
pthread_mutex_t => 16 bytes

*/