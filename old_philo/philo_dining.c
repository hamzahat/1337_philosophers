/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:23:18 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/10 19:24:30 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

//* philo thinking routine
void	philo_think(t_philo *philo)
{
	ft_print(philo, THINK);
}

//* sleep routine of philo;
void	philo_sleep(t_philo *philo)
{
	ft_print(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

//* eat routine of philo;
void	philo_eat(t_philo *philo)
{
	//* take first fork:
	pthread_mutex_lock(&philo->first_fork->fork);
	//* log: take a fork:
	ft_print(philo, FORK);
	//* take the second fork:
	pthread_mutex_lock(&philo->second_fork->fork);
	//* log: take a fork:
	ft_print(philo, FORK);
	//* set last meal time:
	set_last_meal_time(philo, get_time_ms());
	//* increment meals counter:
	increment_meals_counter(philo);
	//! ask chat about this thing ! here i use meal_mutex mutex for both increment_meals and get_meals_counter functions ! is it nomal
	//* log: eating
	ft_print(philo, EAT);
	//* sleep time to eat:
	ft_usleep(philo->table->time_to_eat, philo->table);
	//* set meals_full = true
	if ((philo->table->meals_nb != -1) && (get_meals_counter(philo) == philo->table->meals_nb))
		set_philo_is_full(philo, true);
	//* unloc forks
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

//todo: should I join the monitor threads here !
//* join all threads;
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
	int		i;

	table = (t_table *)arg;

	//* wait for all threads to be ready
	while (!get_threads_ready(table))
		usleep(10);
	while (1)
	{
		//* check if philo die
		i = 0;
		while (i < table->philo_nb)
		{
			if (get_time_ms() - get_last_meal_time(&table->philos_arr[i]) >= table->time_to_die)
			{
				ft_print(&table->philos_arr[i], DIE);
				set_end_simulation(table, true);
				return (NULL);
			}
			i++;
		}
		//* check if all philos are full
		if (table->meals_nb != -1 && all_philos_are_full(table))
			set_end_simulation(table, true);
		usleep(100);
	}
	return (NULL);
}

//* the fun of philosophers routine;
void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;

	//* wait all threads to start at the same time !
	while (!get_threads_ready(philo->table))
		usleep(10);

	//? why I put this set_last_meal_time here! is not enough to put after the philo eat!?
	set_last_meal_time(philo, get_time_ms());

	//* Loop until someone dies or all are full
	while (!get_end_simulation(philo->table))
	{

		//* check if the philo is full ? (number of meals)
		if (get_philo_is_full(philo))
			break ;

		//* eat   (eat routine + log)
		philo_eat(philo);

		//* sleep (ms of sleep time + log)
		philo_sleep(philo);

		//* think (log)
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
	// set_start_time(table);
	table->start_simulation_time = get_time_pass();
	printf("start simulation time = %ld\n", table->start_simulation_time);

	//* after all threads are ready you can start the philos routine;
	set_threads_ready(table, true);

	//* join all threads;
	if (join_threads(table))
		return (ft_putstr_fd(2, "pthread_join failed\n"), 1);

	//* at this point all philos are finishe
	printf("all philos are full!\n");
	return (0);
}
