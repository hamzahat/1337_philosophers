/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:52:18 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 13:25:47 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

//* print str in fd;
void	ft_putstr_fd(int fd, char *str)
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
	if (*str)
		return (-1);
	return ((int)nb);
}

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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

int	join_philos(t_table *table, int nbr_to_join)
{
	int	i;

	i = 0;
	while (i < nbr_to_join)
	{
		if (pthread_join(table->philos_arr[i].thread_id, NULL))
			return (ft_putstr_fd(2, "Error: pthread_join failed\n"), 1);
		i++;
	}
	return (0);
}

void	destroy_forks(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->forks_arr[i]);
		i++;
	}
}

void	destroy_table_last_meal_mtx(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->philos_arr[i].last_meal_mtx);
		i++;
	}
}

void	destroy_table_meal_counter_mtx(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->philos_arr[i].meals_counter_mtx);
		i++;
	}
}

void	destroy_table_philo_is_full_mtx(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->philos_arr[i].philo_is_full_mtx);
		i++;
	}
}

int	ft_strcmp(char *str_1, char *str_2)
{
	int	i;

	i = 0;
	while (str_1[i] && str_2[i] && str_1[i] == str_2[i])
		i++;
	return (str_1[i] - str_2[i]);
}
