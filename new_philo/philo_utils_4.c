/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:25:05 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/16 08:46:10 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	handle_last_meal_mtx_init_failure(t_table *table, int i)
{
	destroy_forks(table, table->philos_nbr);
	pthread_mutex_destroy(&table->write_lock_mtx);
	pthread_mutex_destroy(&table->end_simu_mtx);
	destroy_table_last_meal_mtx(table, i);
	ft_safe_malloc(0, FREE_ALL, NULL);
}

void	handle_meals_counter_mtx_init_failure(t_table *table, int i)
{
	destroy_forks(table, table->philos_nbr);
	pthread_mutex_destroy(&table->write_lock_mtx);
	pthread_mutex_destroy(&table->end_simu_mtx);
	destroy_table_last_meal_mtx(table, i);
	destroy_table_meal_counter_mtx(table, i);
	ft_safe_malloc(0, FREE_ALL, NULL);
}

void	handle_philo_full_mtx_init_failure(t_table *table, int i)
{
	destroy_forks(table, table->philos_nbr);
	pthread_mutex_destroy(&table->write_lock_mtx);
	pthread_mutex_destroy(&table->end_simu_mtx);
	destroy_table_last_meal_mtx(table, i);
	destroy_table_meal_counter_mtx(table, i);
	destroy_table_philo_is_full_mtx(table, i);
	ft_safe_malloc(0, FREE_ALL, NULL);
}

void	init_philo_arr(t_table *table, int i)
{
	table->philos_arr[i].last_meal_time = 0;
	table->philos_arr[i].meals_counter = 0;
	table->philos_arr[i].philo_id = i + 1;
	table->philos_arr[i].philo_is_full = false;
	table->philos_arr[i].table = table;
}

int	allocate_philos_and_forks(t_table *table)
{
	table->philos_arr = ft_safe_malloc(
			sizeof(t_philo) * table->philos_nbr, ALLOCATE, NULL);
	if (!table->philos_arr)
		return (malloc_failed_error());
	table->forks_arr = ft_safe_malloc(
			sizeof(pthread_mutex_t) * table->philos_nbr, ALLOCATE, NULL);
	if (!table->forks_arr)
		return (malloc_failed_error());
	return (0);
}
