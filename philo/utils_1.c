/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:21:13 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/09 22:12:02 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

//? print str in fd;
void    ft_putstr_fd(int fd, char *str)
{
	if (!str)
		return ;
    write(fd, str, ft_strlen(str));
}

//? calculate len of str;
size_t  ft_strlen(char *str)
{
    size_t  i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        ++i;
    return (i);
}

//? converte ascii to integer
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

//? allocate philos array;
int	allocate_philos_arr(t_table *table)
{
	table->philos_arr = ft_safe_malloc(sizeof(t_philo) * table->philo_nb, ALLOCATE, NULL);
	if (!table->philos_arr)
		return (1);
	return (0);
}

//? allocate forks array;
int	allocate_forks_arr(t_table *table)
{
	table->forks_arr = ft_safe_malloc(sizeof(t_fork) * table->philo_nb, ALLOCATE, NULL);
	if (!table->forks_arr)
		return (1);
	return (0);
}

//? clean memory resources;
void	clean_up(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->end_simu_mutex);
	pthread_mutex_destroy(&table->write_lock);
	while (i < table->philo_nb)
	{
	printf("+++++++++++++\n");
		pthread_mutex_destroy(&table->philos_arr[i].meal_mutex);
		i++;
	}
	i = 0;
	while (i < table->philo_nb)
	{
	printf("=======================\n");
		pthread_mutex_destroy(&table->forks_arr[i].fork);
		printf("add of mutex = %p\n", &table->forks_arr[i].fork);
		i++;
	}

	printf("-------------\n");
	ft_safe_malloc(0, FREE_ALL, NULL);
}

//* get the time pass frome the start of the programme until now!
long	get_time_pass(void)
{
	static long	start_time;
	long		current_time;
	t_timeval	time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (start_time == 0)
		start_time = current_time;
	return (current_time - start_time);
}

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

//* increment the value to meals-counter safely;
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

//* print the log safely;
void	ft_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->write_lock);
	pthread_mutex_lock(&philo->table->start_sim_mutex);
	if (!get_end_simulation(philo->table))
		printf("%ld %d %s\n",
			get_time_ms() - philo->table->start_simulation_time,
			philo->philo_id,
			msg);
	pthread_mutex_unlock(&philo->table->start_sim_mutex);
	pthread_mutex_unlock(&philo->table->write_lock);
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

//* set the start time of simulation;
void	set_start_time(t_table *table)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&table->start_sim_mutex);
	table->start_simulation_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	pthread_mutex_unlock(&table->start_sim_mutex);
}

//* get the current time in milliseconds
long	get_time_ms(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL); 
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

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

//* set philo is full
void	set_philo_is_full(t_philo *philo, bool value)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_full = value;
	pthread_mutex_unlock(&philo->meal_mutex);
}

//* check if philo is full
bool	get_philo_is_full(t_philo *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->meal_mutex);
	status = philo->meals_full;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (status);
}

//* check if all philos are full
bool	all_philos_are_full(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nb)
	{
		if (!get_philo_is_full(&table->philos_arr[i]))
			return (false);
		i++;
	}
	return (true);
}

//* debugging functions;
void	printf_input_data(t_table table)
{
	printf("correct input!\n");
	printf("number_of_philosophers: %d\n", table.philo_nb);
	printf("time_to_die: %d\n", table.time_to_die);
	printf("time_to_eat: %d\n", table.time_to_eat);
	printf("time_to_sleep: %d\n", table.time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat: %d\n", table.meals_nb);
}
