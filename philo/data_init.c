/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:57:14 by hamza_hat         #+#    #+#             */
/*   Updated: 2025/08/07 15:30:10 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

//* assign forks for every philo in the table;
static void	assign_forks_to_philos(t_philo *philo, t_fork *forks, int philo_pos)
{
	if ((philo->philo_id % 2) != 0) //* odd (1 3 5)
	{
		philo->first_fork = &forks[(philo_pos + 1) % philo->table->philo_nb];
		philo->second_fork = &forks[philo_pos];
	}
	else //* even (2 4 6)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo->table->philo_nb];
	}
}

//* initialize table struct with default values;
int	initialize_table_data(t_table *table)
{
	if (!table)
		return (1);
	memset(table, 0, sizeof(*table));
	table->meals_nb = -1;
	if (pthread_mutex_init(&table->end_simu_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&table->write_lock, NULL))
		return (1);
	if (pthread_mutex_init(&table->threads_ready_mtx, NULL))
		return (1);
	return (0);
}

//* initialyze forks data;
int	forks_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_mutex_init(&table->forks_arr[i].fork, NULL))
			return (ft_putstr_fd(2 ,"pthread_mutex_init failed\n"), 1);
		table->forks_arr[i].fork_id = i;
		i++;
	}
	return (0);
}

//* initialyze philos data;
int	philos_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		table->philos_arr[i].last_meal_time = 0;
		table->philos_arr[i].philo_id = i + 1;
		table->philos_arr[i].meals_counter = 0;
		table->philos_arr[i].meals_full = false;
		table->philos_arr[i].table = table;
		if (pthread_mutex_init(&table->philos_arr[i].meal_mutex, NULL))
			return (ft_putstr_fd(2 ,"pthread_mutex_init failed\n"), 1);
		assign_forks_to_philos(&table->philos_arr[i], table->forks_arr, i);
		i++;
	}
	return (0);
}

//* initialyze philos threads;
int	init_philos_and_monitor_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		if (pthread_create(&table->philos_arr[i].thread_id, NULL, philo_routine, &table->philos_arr[i]))
			return (1);
		i++;
	}
	if (pthread_create(&table->monitor, NULL, monitor_fun, table))
		return (1);
	return (0);
}

//* initialyze data table;
int	data_init(t_table *table)
{
	if (forks_init(table) || philos_init(table))
		return (1);
	return (0);
}
