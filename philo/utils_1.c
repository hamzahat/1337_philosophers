/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:21:13 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/04 15:31:44 by hbenmoha         ###   ########.fr       */
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
void	clean_up(void)
{
	ft_safe_malloc(0, FREE_ALL, NULL);
}

//? get the time pass frome the start of the programme until now!
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

//? debugging functions;
void	printf_input_data(t_table table)
{
	printf("correct input!\n");
	printf("number_of_philosophers: %d\n", table.philo_nb);
	printf("time_to_die: %d\n", table.time_to_die);
	printf("time_to_eat: %d\n", table.time_to_eat);
	printf("time_to_sleep: %d\n", table.time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat: %d\n", table.meals_nb);
}
