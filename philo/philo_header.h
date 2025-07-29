/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza_hat <hamza_hat@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:35:19 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/07/29 13:11:56 by hamza_hat        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//* * * headers * * *//

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

//* * * structures * * *//

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

typedef struct s_philo
{
	t_fork			*left_fork;			//?
	t_fork			*right_fork;		//?
	long			last_meal_time;		//?
	int				philo_id;			//?
	int				nb_meals;			//?
	pthread_t		thread_id;			//? philo is thread id
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	fork;		//?
	int				fork_id;	//?
}	t_fork;

//* * * functions prototypes * * *//

int		parse_intput(int ac, char *av[], t_table *table);
void    ft_putstr_fd(int fd, char *str);
size_t	ft_strlen(char *str);

#endif

/*
* * * structs & typedefs size:
pthread_t       => 72 bytes
pthread_mutex_t => 16 bytes

*/