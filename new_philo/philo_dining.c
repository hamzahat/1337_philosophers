/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:56:05 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 13:01:34 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	ft_print(philo, FORK);
	pthread_mutex_lock(philo->second_fork);
	ft_print(philo, FORK);
	set_last_meal_time(philo, get_time_ms());
	increment_meals_counter(philo);
	ft_print(philo, EAT);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals_nbr != -1 && get_meals_counter(philo) == philo->table->meals_nbr)
		set_philo_is_full(philo, true);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	philo_sleep(t_philo *philo)
{
	ft_print(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	philo_think(t_philo *philo)
{
	ft_print(philo, THINK);
	// if (philo->table->philos_nbr % 2 != 0) //! should I keep it !? and why !?
	// 	usleep(100);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_last_meal_time(philo, philo->table->start_simulation_time); //! why this !?
	if (philo->table->philos_nbr == 1)
	{
		pthread_mutex_lock(philo->first_fork);
		ft_print(philo, FORK);
		ft_usleep(philo->table->time_to_die, philo->table);
		pthread_mutex_unlock(philo->first_fork);
		return (NULL);
	}
	while (!get_end_simulation(philo->table))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	usleep(1000);
	while (!get_end_simulation(table))
	{
		i = 0;
		while (i < table->philos_nbr && !get_end_simulation(table))
		{
			if ((get_time_ms() - get_last_meal_time(&table->philos_arr[i])) > table->time_to_die)
			{
				set_end_simulation(table, true);
				ft_print(&table->philos_arr[i], DIE);
				return (NULL);
			}
			i++;
		}
		if (table->meals_nbr != -1 && all_philos_are_full(table))
			set_end_simulation(table, true);
		usleep(100);
	}
	return (NULL);
}

int	dining_start(t_table *table)
{
	int	i;

	i = 0;
	table->start_simulation_time = get_time_ms();
	while (i < table->philos_nbr)
	{
		if (pthread_create(&table->philos_arr[i].thread_id, NULL, philo_routine, &table->philos_arr[i]))
		{
			ft_putstr_fd(2, "Error: pthread_create failed\n");
			set_end_simulation(table, true);
			join_philos(table, i);
			return (1);
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL, monitor_routine, table))
	{
		ft_putstr_fd(2, "Error: pthread_create failed\n");
		set_end_simulation(table, true);
		join_philos(table, table->philos_nbr);
		return (1);
	}
	if (join_philos(table, table->philos_nbr))
		return (1);
	if (pthread_join(table->monitor, NULL))
		return (ft_putstr_fd(2, "Error: pthread_join failed\n"), 1);
	return (0);
}
