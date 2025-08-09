/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza_hat <hamza_hat@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:50:36 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/08 14:33:12 by hamza_hat        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

//* join all threads
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

//* the fun of monitor func that will check if other philos (die/full);
void	*monitor_fun(void	*arg)
{
	t_table	*table;

	table = (t_table *)arg;
	//todo: check if any philo die!
	//todo: check if philos eat the number of meals_nb (it it has been set)
	return (NULL);
}

//todo: inside the philo_routine fun make eat + sleep + thinking functions/actions

//* the fun of philosophers routine;
void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;

//* wait all threads to start at the same time !
	while (!get_threads_ready(philo->table))
		usleep(10);
	
	//todo: set last meal time (to check if philo diead)

//* Loop until someone dies or all are full
	while (!get_end_simulation(philo->table))
	{

	//* check if the philo is full ? (number of meals)
		if (philo->table->meals_nb != -1)
			if (get_meals_counter(philo) == philo->table->meals_nb)
				break ;

		//todo: eat   (eat routine + log)
		philo_eat(philo);

		//todo: sleep (ms of sleep time + log)
		philo_sleep(philo);

		//todo: think (print thinking)
		philo_think(philo);

	}

	return (NULL);
}

//* the main fun of philosophers dining routine start;
int	philo_dining_start(t_table *table)
{
//* make threads (philos + monitor);
	if (init_philos_and_monitor_threads(table))
		return (ft_putstr_fd(2, "pthread_create failed\n"), 1);

//* set the start time of simulation;
	set_start_time(table);

//* after all threads are ready you can start the philos routine;
	set_threads_ready(table, true);

//* join all threads;
	if (join_threads(table))
		return (ft_putstr_fd(2, "pthread_join failed\n"), 1);

//* at this point all philos finished

	return (0);
}
