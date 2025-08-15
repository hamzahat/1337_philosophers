/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:44:43 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 16:56:24 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	malloc_failed_error(void)
{
	return (
		ft_putstr_fd(2, "memory allocation failed\n"),
		ft_safe_malloc(0, FREE_ALL, NULL),
		1);
}

static int	pthread_mutex_init_failed_error(void)
{
	return (
		ft_safe_malloc(0, FREE_ALL, NULL),
		ft_putstr_fd(2, "pthread_mutex_init failed\n"),
		1);
}

static int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		init_philo_arr(table, i);
		if (pthread_mutex_init(&table->philos_arr[i].last_meal_mtx, NULL))
		{
			handle_last_meal_mtx_init_failure(table, i);
			return (ft_putstr_fd(2, "mutex_init failed\n"), 1);
		}
		if (pthread_mutex_init(&table->philos_arr[i].meals_counter_mtx, NULL))
		{
			handle_meals_counter_mtx_init_failure(table, i);
			return (ft_putstr_fd(2, "mutex_init failed\n"), 1);
		}
		if (pthread_mutex_init(&table->philos_arr[i].philo_is_full_mtx, NULL))
		{
			handle_philo_full_mtx_init_failure(table, i);
			return (ft_putstr_fd(2, "mutex_init failed\n"), 1);
		}
		assign_forks(&table->philos_arr[i], table, i);
		i++;
	}
	return (0);
}

void	assign_forks(t_philo *philo, t_table *table, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = table->philos_nbr;
	if (philo->philo_id % 2 == 0)
	{
		philo->first_fork = &table->forks_arr[philo_pos];
		philo->second_fork = &table->forks_arr[(philo_pos + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &table->forks_arr[(philo_pos + 1) % philo_nbr];
		philo->second_fork = &table->forks_arr[philo_pos];
	}
}

int	data_init(char *av[], t_table *table)
{
	table->philos_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meals_nbr = ft_atoi(av[5]);
	else
		table->meals_nbr = -1;
	table->start_simulation_time = 0;
	table->end_simulation = false;
	if (allocate_philos_and_forks(table))
		return (1);
	if (pthread_mutex_init(&table->end_simu_mtx, NULL))
		return (pthread_mutex_init_failed_error());
	if (pthread_mutex_init(&table->write_lock_mtx, NULL))
		return (
			pthread_mutex_destroy(&table->end_simu_mtx),
			pthread_mutex_init_failed_error());
	if (init_forks(table))
		return (1);
	if (init_philos(table))
		return (1);
	return (0);
}
