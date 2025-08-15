/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:11:21 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 14:12:20 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	destroy_forks(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks_arr[i]);
		i++;
	}
}

void	destroy_table_last_meal_mtx(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->philos_arr[i].last_meal_mtx);
		i++;
	}
}

void	destroy_table_meal_counter_mtx(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->philos_arr[i].meals_counter_mtx);
		i++;
	}
}

void	destroy_table_philo_is_full_mtx(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->philos_arr[i].philo_is_full_mtx);
		i++;
	}
}

int	join_philos(t_table *table, int nbr_to_join)
{
	int	i;

	i = 0;
	while (i < nbr_to_join)
	{
		if (pthread_join(table->philos_arr[i].thread_id, NULL))
			return (ft_putstr_fd(2, "Error: pthread_join failed\n"), 1);
		i++;
	}
	return (0);
}
