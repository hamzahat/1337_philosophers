/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:35:19 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/07/30 17:23:27 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

//* * * structures * * *//

//? ft_saf_malloc struct:
typedef struct s_mem_node
{
	void				*address;
	struct s_mem_node	*next;
}						t_mem_node;

typedef struct s_fork
{
	pthread_mutex_t	fork;		//?
	int				fork_id;	//?
}	t_fork;

typedef struct s_philo
{
	t_fork			*left_fork;			//?
	t_fork			*right_fork;		//?
	long			last_meal_time;		//?
	int				philo_id;			//?
	int				nb_meals;			//?
	pthread_t		thread_id;			//? philo is thread id
}	t_philo;

typedef struct s_table
{
	t_philo			*philos_arr;	//? ptr to an array of philos ( t_philo struct )
	t_fork			*forks_arr;		//? ptr to an array of forks ( mutex )
	int				philo_nb;		//? number of philos ( from argv )
	int				time_to_die;	//?
	int				time_to_eat;	//?
	int				time_to_sleep;	//?
	int				meals_nb;		//? number of meals every philo should eat!
}	t_table;


//* * * functions prototypes * * *//

//? --- parsing functions ---

int		parse_intput(int ac, char *av[], t_table *table);
void	ft_putstr_fd(int fd, char *str);
size_t	ft_strlen(char *str);
int		check_args_number(int ac);
int		converte_args_to_nb(t_table *table, char *av[]);
int		ft_atoi(char *str);
void	printf_input_data(t_table table);
void	initialize_table_data(t_table *table);

//? --- data initialization ---

void	philos_init(t_table *table);
void	forks_init(t_table *table);

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