/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:52:18 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/14 12:26:18 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

//* print str in fd;
void    ft_putstr_fd(int fd, char *str)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

//* calculate len of str;
size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		++i;
	return (i);
}

//* converte ascii to integer
int	ft_atoi(char *str)
{
	long	nb;

	nb = 0;
	if (!str)
		return (-1);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '+' && (*(str + 1) >= '0' && *(str + 1) <= '9'))
			++str;
		else
			return (-1);
	}
	if (*str < '0' || *str > '9')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str++ - 48);
		if (nb > INT_MAX)
			return (-1);
	}
	return ((int)nb);
}

//todo: check when the gettimeofday fun failed
long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL); 
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//* set the time to last-meal-time var safely;
void	set_last_meal_time(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->last_meal_mtx);
}

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

void	ft_print(t_philo *philo, char *msg)
{
	long	elapsed_time;

	pthread_mutex_lock(&philo->table->write_lock_mtx);
	elapsed_time = get_time_ms() - philo->table->start_simulation_time;

	if (get_end_simulation(philo->table) && strcmp(msg, DIE) != 0)
	{
		pthread_mutex_unlock(&philo->table->write_lock_mtx);
		return ;
	}
	printf("%ld %d %s\n", elapsed_time, philo->philo_id, msg);
	pthread_mutex_unlock(&philo->table->write_lock_mtx);
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

//* sleep specific time + check if simulation finished;
void	ft_usleep(long	time_in_ms, t_table *table)
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

//* get the value from last-meal-time safely;
long	get_last_meal_time(t_philo *philo)
{
	long	meal_time;

	pthread_mutex_lock(&philo->last_meal_mtx);
	meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->last_meal_mtx);
	return (meal_time);
}

//* set philo is full safely;
void	set_philo_is_full(t_philo *philo, bool value)
{
	pthread_mutex_lock(&philo->philo_is_full_mtx);
	philo->philo_is_full = value;
	pthread_mutex_unlock(&philo->philo_is_full_mtx);
}

//* check if philo is full safely;
bool	get_philo_is_full(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->philo_is_full_mtx);
	status = philo->philo_is_full;
	pthread_mutex_unlock(&philo->philo_is_full_mtx);
	return (status);
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

void	clean_up(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		pthread_mutex_destroy(&table->forks_arr[i]);
		pthread_mutex_destroy(&table->philos_arr[i].last_meal_mtx);
		pthread_mutex_destroy(&table->philos_arr[i].meals_counter_mtx);
		pthread_mutex_destroy(&table->philos_arr[i].philo_is_full_mtx);
		i++;
	}
	pthread_mutex_destroy(&table->end_simu_mtx);
	pthread_mutex_destroy(&table->write_lock_mtx);
	ft_safe_malloc(0, FREE_ALL, NULL);
}
