/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_and_setters_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:20:41 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 13:32:50 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

//* get the value of end-of-simulation safely;
bool	get_end_simulation(t_table *table)
{
	bool	status;

	pthread_mutex_lock(&table->end_simu_mtx);
	status = table->end_simulation;
	pthread_mutex_unlock(&table->end_simu_mtx);
	return (status);
}

//* set the value of end-of-simulation safely;
void	set_end_simulation(t_table *table, bool value)
{
	pthread_mutex_lock(&table->end_simu_mtx);
	table->end_simulation = value;
	pthread_mutex_unlock(&table->end_simu_mtx);
}

//* increment the value of meals-counter safely;
void	increment_meals_counter(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_counter_mtx);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->meals_counter_mtx);
}

//* get the value forme meals-counter safely;
int	get_meals_counter(t_philo *philo)
{
	int	count;

	pthread_mutex_lock(&philo->meals_counter_mtx);
	count = philo->meals_counter;
	pthread_mutex_unlock(&philo->meals_counter_mtx);
	return (count);
}
