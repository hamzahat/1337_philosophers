/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:44:29 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/12 19:04:14 by hbenmoha         ###   ########.fr       */
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
	pthread_mutex_t	*first_fork;			//? done
	pthread_mutex_t	*second_fork;			//? done
	long			last_meal_time;			//? done
	int				meals_counter;			//? done
	int				philo_id;				//? done
	bool			philo_is_full;			//? done
	pthread_t		thread_id;				//* not initialyzed yet!
	t_table			*table;					//? done
}					t_philo;

//? table struct:
struct s_table
{
	t_philo			*philos_arr;			//? done
	pthread_mutex_t	*forks_arr;				//? done
	pthread_t		monitor;				//* not initialyzed yet!
	int				philos_nbr;				//? done
	int				time_to_die;			//? done
	int				time_to_eat;			//? done
	int				time_to_sleep;			//? done
	int				meals_nbr;				//? done
	long			start_simulation_time;	//? done
	bool			end_simulation;			//? done
	pthread_mutex_t	end_simu_mtx;			//? done
	pthread_mutex_t	write_lock_mtx;			//? done
	//todo: add mutexs
};

//* * * Functions prototypes * * *//
int		parse_input(int ac, char *av[]);
void    ft_putstr_fd(int fd, char *str);
size_t	ft_strlen(char *str);
int		ft_atoi(char *str);
void	*ft_safe_malloc(size_t size, int key, void *to_delete);
int		data_init(char *av[], t_table *table);


void	print_data_debugging(t_table *table);


#endif
