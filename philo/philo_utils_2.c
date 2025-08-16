/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:11:02 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 16:49:56 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

//* print philo actions safely;
void	ft_print(t_philo *philo, char *msg)
{
	long	elapsed_time;

	pthread_mutex_lock(&philo->table->write_lock_mtx);
	elapsed_time = get_time_ms() - philo->table->start_simulation_time;
	if (get_end_simulation(philo->table) && ft_strcmp(msg, DIE) != 0)
	{
		pthread_mutex_unlock(&philo->table->write_lock_mtx);
		return ;
	}
	printf("%ld %d %s\n", elapsed_time, philo->philo_id, msg);
	pthread_mutex_unlock(&philo->table->write_lock_mtx);
}

//* sleep specific time (ms) + check if simulation finished;
void	ft_usleep(long time_in_ms, t_table *table)
{
	long	start_time;

	start_time = get_time_ms();
	while (!get_end_simulation(table))
	{
		if (get_time_ms() - start_time >= time_in_ms)
			break ;
		usleep(100);
	}
}

//* check if all philos are full
bool	all_philos_are_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		if (!get_philo_is_full(&table->philos_arr[i]))
			return (false);
		i++;
	}
	return (true);
}

int	create_philos_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		if (pthread_create(
				&table->philos_arr[i].thread_id, NULL, philo_routine,
				&table->philos_arr[i]))
		{
			ft_putstr_fd(2, "Error: pthread_create failed\n");
			set_end_simulation(table, true);
			join_philos(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
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
	return (0);
}
