/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:44:43 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 12:33:32 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

static void	assign_forks(t_philo *philo, t_table *table, int philo_pos)
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
	int	i;

	i = 0;
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
	table->philos_arr = ft_safe_malloc(sizeof(t_philo) * table->philos_nbr, ALLOCATE, NULL);
	if (!table->philos_arr)
		return (ft_putstr_fd(2, "memory allocation failed\n"), ft_safe_malloc(0, FREE_ALL, NULL), 1);
	table->forks_arr = ft_safe_malloc(sizeof(pthread_mutex_t) * table->philos_nbr, ALLOCATE, NULL);
	if (!table->forks_arr)
		return (ft_putstr_fd(2, "memory allocation failed\n"), ft_safe_malloc(0, FREE_ALL, NULL), 1);
	if (pthread_mutex_init(&table->end_simu_mtx, NULL))
		return (ft_safe_malloc(0, FREE_ALL, NULL), ft_putstr_fd(2, "pthread_mutex_init failed\n"), 1);
	if (pthread_mutex_init(&table->write_lock_mtx, NULL))
		return (pthread_mutex_destroy(&table->end_simu_mtx), ft_safe_malloc(0, FREE_ALL, NULL), ft_putstr_fd(2, "pthread_mutex_init failed\n"), 1);
	while (i < table->philos_nbr)
	{
		if (pthread_mutex_init(&table->forks_arr[i], NULL))
		{
			destroy_forks(table, i);
			pthread_mutex_destroy(&table->write_lock_mtx);
			pthread_mutex_destroy(&table->end_simu_mtx);
			ft_safe_malloc(0, FREE_ALL, NULL);
			return (ft_putstr_fd(2, "mutex_init failed\n"), 1);
		}
		i++;
	}
	i = 0;
	while (i < table->philos_nbr)
	{
		table->philos_arr[i].last_meal_time = 0;
		table->philos_arr[i].meals_counter = 0;
		table->philos_arr[i].philo_id = i + 1;
		table->philos_arr[i].philo_is_full = false;
		table->philos_arr[i].table = table;
		if (pthread_mutex_init(&table->philos_arr[i].last_meal_mtx, NULL))
		{
			destroy_forks(table, table->philos_nbr);
			pthread_mutex_destroy(&table->write_lock_mtx);
			pthread_mutex_destroy(&table->end_simu_mtx);
			destroy_table_last_meal_mtx(table, i);
			ft_safe_malloc(0, FREE_ALL, NULL);
			return (ft_putstr_fd(2, "mutex_init failed\n"), 1);
		}
		if (pthread_mutex_init(&table->philos_arr[i].meals_counter_mtx, NULL))
		{
			destroy_forks(table, table->philos_nbr);
			pthread_mutex_destroy(&table->write_lock_mtx);
			pthread_mutex_destroy(&table->end_simu_mtx);
			destroy_table_last_meal_mtx(table, i);
			destroy_table_meal_counter_mtx(table, i);
			ft_safe_malloc(0, FREE_ALL, NULL);
			return (ft_putstr_fd(2, "mutex_init failed\n"), 1);
		}
		if (pthread_mutex_init(&table->philos_arr[i].philo_is_full_mtx, NULL))
		{
			destroy_forks(table, table->philos_nbr);
			pthread_mutex_destroy(&table->write_lock_mtx);
			pthread_mutex_destroy(&table->end_simu_mtx);
			destroy_table_last_meal_mtx(table, i);
			destroy_table_meal_counter_mtx(table, i);
			destroy_table_philo_is_full_mtx(table, i);
			ft_safe_malloc(0, FREE_ALL, NULL);
			return (ft_putstr_fd(2, "mutex_init failed\n"), 1);
		}
		assign_forks(&table->philos_arr[i], table, i);
		i++;
	}
	return (0);
}
