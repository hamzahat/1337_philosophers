/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:44:43 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/13 16:59:28 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

static void	assign_forks(t_philo *philo, t_table *table, int philo_pos)
{
	int philo_nbr;

	philo_nbr = table->philos_nbr;

	if (philo->philo_id % 2 == 0)
	{
		philo->first_fork = &table->forks_arr[philo_pos];
		philo->second_fork = &table->forks_arr[(philo_pos + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &table->forks_arr[(philo_pos + 1) % philo_nbr];
		philo->second_fork = &table->forks_arr[philo_pos];
	}
}

int	data_init(char *av[], t_table *table)
{
	int	i;

	i = 0;
	table->philos_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meals_nbr = ft_atoi(av[5]);
	else
		table->meals_nbr = -1;
	table->start_simulation_time = 0;
	table->end_simulation = false;
	table->philos_arr = ft_safe_malloc(sizeof(t_philo) * table->philos_nbr, ALLOCATE, NULL);
	if (!table->philos_arr)
		return (ft_putstr_fd(2, "memory allocation failed\n"), ft_safe_malloc(0, FREE_ALL, NULL), 1);
	table->forks_arr = ft_safe_malloc(sizeof(pthread_mutex_t) * table->philos_nbr, ALLOCATE, NULL);
	if (!table->forks_arr)
		return (ft_putstr_fd(2, "memory allocation failed\n"), ft_safe_malloc(0, FREE_ALL, NULL), 1);
	pthread_mutex_init(&table->end_simu_mtx, NULL);
	pthread_mutex_init(&table->write_lock_mtx, NULL);
	while (i < table->philos_nbr)
	{
		pthread_mutex_init(&table->forks_arr[i], NULL);
		i++;
	}
	i = 0;
	while (i < table->philos_nbr)
	{
		table->philos_arr[i].last_meal_time = 0;
		table->philos_arr[i].meals_counter = 0;
		table->philos_arr[i].philo_id = i + 1;
		table->philos_arr[i].philo_is_full = false;
		// table->philos_arr[i].first_fork =  &table->forks_arr[i]; //todo: remove those lines 
		// table->philos_arr[i].second_fork = &table->forks_arr[(i + 1) % table->philos_nbr];
		table->philos_arr[i].table = table;
		pthread_mutex_init(&table->philos_arr[i].last_meal_mtx, NULL);
		pthread_mutex_init(&table->philos_arr[i].meals_counter_mtx, NULL);
		pthread_mutex_init(&table->philos_arr[i].philo_is_full_mtx, NULL);
		assign_forks(&table->philos_arr[i], table, i);
		i++;
	}
	return (0);
}

void	print_data_debugging(t_table *table)
{
	int i = -1;
	printf("philos nbr    => %d\n", table->philos_nbr);
	printf("time to die   => %d\n",table->time_to_die);
	printf("time to eat   => %d\n", table->time_to_eat);
	printf("time to sleep => %d\n", table->time_to_sleep);
	printf("meals nbr     => %d\n", table->meals_nbr);
	printf("start simulation time => %ld\n",table->start_simulation_time);
	printf("end simulation flag => %d\n", table->end_simulation);
	printf("end simu mtx        => %p\n", &table->end_simu_mtx);
	printf("write_lock_mtx      => %p\n", &table->write_lock_mtx);
	while (++i < table->philos_nbr)
		printf("forks mutexs    => %p\n", &table->forks_arr[i]);
	i = -1;
	printf("philo data:\n");
	while (++i < table->philos_nbr)
	{
		printf("last meal time => %ld\n", table->philos_arr[i].last_meal_time);
		printf("meals counter  => %d\n", table->philos_arr[i].meals_counter);
		printf("philo id       => %d\n", table->philos_arr[i].philo_id);
		printf("philo is full  => %d\n", table->philos_arr[i].philo_is_full);
		printf("table ptr forme every philo => %p\n", table->philos_arr[i].table);
		printf("last meal mutex => %p\n", &table->philos_arr[i].last_meal_mtx);
		printf("first fork     => %lu\n", (unsigned long)(uintptr_t)table->philos_arr[i].first_fork);
		printf("second fork    => %lu\n", (unsigned long)(uintptr_t)table->philos_arr[i].second_fork);
		
	}
	
}
