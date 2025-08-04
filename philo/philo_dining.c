/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:50:36 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/04 17:03:53 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_join(table->philos_arr[i].thread_id, NULL))
			return (1);
		i++;
	}
	if (pthread_join(table->monitor, NULL))
		return (1);
	return (0);
}

//? the fun of monitor func that will controll check other philos (die/full);
void	*monitor_fun(void	*arg)
{
	//t_table	*table;
	(void)arg;

//	table = (t_table *)arg;
	//todo: check if any philo die!
	//todo: check if philos eat the number of meals_nb (it it has been set)
	return (NULL);
}

//todo: inside the philo_routine fun make eat + sleep + thinking functions/actions

//? the fun of philosophers routine;
void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!philo->table->end_simulation) //* Loop until someone dies or all are full
	{
//* Take first fork → log
	pthread_mutex_lock(&philo->first_fork->fork);
	printf("%ld %d has taken a fork_id => %d\n", get_time_pass(), philo->philo_id, philo->first_fork->fork_id);
//* Take second fork → log
	pthread_mutex_lock(&philo->second_fork->fork);
	printf("%ld %d has taken a fork_id => %d\n", get_time_pass(), philo->philo_id, philo->second_fork->fork_id);
//todo: Eat → update last_meal_time, log, usleep(time_to_eat)
	printf("%ld %d is eating\n", get_time_pass(), philo->philo_id);
	usleep(philo->table->time_to_eat * 1000);
//* Unlock both forks
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
//* Sleep → log, usleep(time_to_sleep)
	printf("%ld %d is sleeping\n", get_time_pass(), philo->philo_id);
	usleep(philo->table->time_to_sleep * 1000);
//* Think → log
	printf("%ld %d is thinking\n", get_time_pass(), philo->philo_id);
	}
	
	
	return (NULL);
}

//? the main fun of philosophers dining routine;
int	philo_dining_start(t_table *table)
{
	if (init_philos_and_monitor_threads(table))
		return (ft_putstr_fd(2, "pthread_create failed\n"), 1);
	if (join_threads(table))
		return (ft_putstr_fd(2, "pthread_join failed\n"), 1);
	//todo: handle if the philo number is 1

	return (0);
}
