/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:44:29 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 12:09:27 by hbenmoha         ###   ########.fr       */
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

//* * * Philo routine messages * * *//

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

//* * * Macros * * *//

# define N_OF_PHILO "number_of_philosophers"
# define N_OF_MEALS "number_of_times_each_philosopher_must_eat"

//* * * Structures * * *//

typedef struct s_table	t_table;

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
	pthread_mutex_t	meals_counter_mtx;
	int				philo_id;
	bool			philo_is_full;
	pthread_mutex_t	philo_is_full_mtx;
	pthread_t		thread_id;
	t_table			*table;
	pthread_mutex_t	last_meal_mtx;
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
};

//* * * Functions prototypes * * *//

int		parse_input(int ac, char *av[]);
void	ft_putstr_fd(int fd, char *str);
size_t	ft_strlen(char *str);
int		ft_atoi(char *str);
void	ft_print(t_philo *philo, char *msg);
void	ft_usleep(long time_in_ms, t_table *table);
int		ft_strcmp(char *str_1, char *str_2);
void	*ft_safe_malloc(size_t size, int key, void *to_delete);
void	clean_up(t_table *table);
int		data_init(char *av[], t_table *table);
int		dining_start(t_table *table);
int		join_philos(t_table *table, int nbr_to_join);
void	destroy_forks(t_table *table, int count);
void	destroy_table_last_meal_mtx(t_table *table, int count);
void	destroy_table_meal_counter_mtx(t_table *table, int count);
void	destroy_table_philo_is_full_mtx(t_table *table, int count);
void	increment_meals_counter(t_philo *philo);
void	set_philo_is_full(t_philo *philo, bool value);
void	set_last_meal_time(t_philo *philo, long time);
long	get_time_ms(void);
void	set_end_simulation(t_table *table, bool value);
long	get_last_meal_time(t_philo *philo);
int		get_meals_counter(t_philo *philo);
bool	get_end_simulation(t_table *table);
bool	get_philo_is_full(t_philo *philo);
bool	all_philos_are_full(t_table *table);

#endif
