/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:56:05 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 16:45:00 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

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
			if ((get_time_ms() - get_last_meal_time(&table->philos_arr[i]))
				> table->time_to_die)
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
	if (create_philos_threads(table))
		return (1);
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
