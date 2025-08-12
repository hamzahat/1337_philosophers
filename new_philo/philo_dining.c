/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:56:05 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/12 21:24:00 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	*philo_routine(void *arg)
{
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	return (NULL);
}
int	dining_start(t_table *table)
{
	int	i;

	i = 0;

	while (i < table->philos_nbr)
	{
		pthread_create(&table->philos_arr[i].thread_id, NULL, philo_routine, &table->philos_arr[i]);
		i++;
	}

	pthread_create(&table->monitor, NULL, monitor_routine, table);
	//todo: set simulation start time
	table->start_simulation_time = 

	i = 0;
	while (i < table->philos_nbr)
	{
		pthread_join(table->philos_arr[i].philo_id, NULL);
		i++;
	}
	
	return (0);
}
