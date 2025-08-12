/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_and_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:58:10 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/10 15:02:55 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

// * * * Getters and Setters * * * //

//* get the value of end-of-simulation safely;
bool	get_end_simulation(t_table *table)
{
	bool	status;

	pthread_mutex_lock(&table->end_simu_mutex);
	status = table->end_simulation;
	pthread_mutex_unlock(&table->end_simu_mutex);
	return (status);
}

//* set the value of end-of-simulation safely;
void	set_end_simulation(t_table *table, bool value)
{
	pthread_mutex_lock(&table->end_simu_mutex);
	table->end_simulation = value;
	pthread_mutex_unlock(&table->end_simu_mutex);
}

//* get the value forme meals-counter safely;
int	get_meals_counter(t_philo *philo)
{
	int	count;

	pthread_mutex_lock(&philo->meal_mutex);
	count = philo->meals_counter;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (count);
}

//* increment the value of meals-counter safely;
void	increment_meals_counter(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

//* get the value from last-meal-time safely;
long	get_last_meal_time(t_philo *philo)
{
	long	meal_time;

	pthread_mutex_lock(&philo->meal_mutex);
	meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (meal_time);
}

//* set the time to last-meal-time var safely;
void	set_last_meal_time(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->meal_mutex);
}

//* set the start time of simulation;
// void	set_start_time(t_table *table)
// {
// 	t_timeval	time;

// 	gettimeofday(&time, NULL);
// 	pthread_mutex_lock(&table->start_sim_mutex);
// 	// table->start_simulation_time = get_time_ms();
// 	table->start_simulation_time = get_time_pass();
// 	pthread_mutex_unlock(&table->start_sim_mutex);
// }

//* set a value to threads_ready bool;
void	set_threads_ready(t_table *table, bool value)
{
	pthread_mutex_lock(&table->threads_ready_mtx);
	table->threads_ready = value;
	pthread_mutex_unlock(&table->threads_ready_mtx);
}

//* get a value from threads_ready safely;
bool	get_threads_ready(t_table *table)
{
	bool	status;

	pthread_mutex_lock(&table->threads_ready_mtx);
	status = table->threads_ready;
	pthread_mutex_unlock(&table->threads_ready_mtx);
	return (status);
}

//* set philo is full safely;
void	set_philo_is_full(t_philo *philo, bool value)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_full = value;
	pthread_mutex_unlock(&philo->meal_mutex);
}

//* check if philo is full safely;
bool	get_philo_is_full(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->meal_mutex);
	status = philo->meals_full;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (status);
}

