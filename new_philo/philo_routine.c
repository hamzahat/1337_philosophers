/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:50:41 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 19:18:03 by hbenmoha         ###   ########.fr       */
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
	if (philo->table->meals_nbr != -1
		&& get_meals_counter(philo) == philo->table->meals_nbr)
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
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_last_meal_time(philo, philo->table->start_simulation_time);
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
