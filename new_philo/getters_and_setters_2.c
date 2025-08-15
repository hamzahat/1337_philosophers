/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_and_setters_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:31:14 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 13:32:47 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

//* check if philo is full safely;
bool	get_philo_is_full(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->philo_is_full_mtx);
	status = philo->philo_is_full;
	pthread_mutex_unlock(&philo->philo_is_full_mtx);
	return (status);
}

//* set philo is full safely;
void	set_philo_is_full(t_philo *philo, bool value)
{
	pthread_mutex_lock(&philo->philo_is_full_mtx);
	philo->philo_is_full = value;
	pthread_mutex_unlock(&philo->philo_is_full_mtx);
}

//* get the value from last-meal-time safely;
long	get_last_meal_time(t_philo *philo)
{
	long	meal_time;

	pthread_mutex_lock(&philo->last_meal_mtx);
	meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_mtx);
	return (meal_time);
}

//* set the time to last-meal-time var safely;
void	set_last_meal_time(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->last_meal_mtx);
}
