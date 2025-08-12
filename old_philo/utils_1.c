/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:21:13 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/10 15:09:10 by hbenmoha         ###   ########.fr       */
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

//* allocate philos array;
int	allocate_philos_arr(t_table *table)
{
	table->philos_arr = ft_safe_malloc(sizeof(t_philo) * table->philo_nb, ALLOCATE, NULL);
	if (!table->philos_arr)
		return (1);
	return (0);
}

//* allocate forks array;
int	allocate_forks_arr(t_table *table)
{
	table->forks_arr = ft_safe_malloc(sizeof(t_fork) * table->philo_nb, ALLOCATE, NULL);
	if (!table->forks_arr)
		return (1);
	return (0);
}

//* clean memory resources;
void	clean_up(t_table *table) //todo: join threads if someting failed then destroy mutexs
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->end_simu_mutex);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->threads_ready_mtx);
	while (i < table->philo_nb)
	{
		pthread_mutex_destroy(&table->philos_arr[i].meal_mutex);
		pthread_mutex_destroy(&table->forks_arr[i].fork);
		i++;
	}
	ft_safe_malloc(0, FREE_ALL, NULL);
}

//* get the time pass from the start of the program until now!
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

//* print the log safely;
void	ft_print(t_philo *philo, char *msg)
{
	if (get_philo_is_full(philo)) //* Redundant check ;( becaus i already check if simulation finished
		return ;
	pthread_mutex_lock(&philo->table->write_lock);
	// pthread_mutex_lock(&philo->table->start_sim_mutex);
	if (!get_end_simulation(philo->table))
		printf("%ld %d %s\n", get_time_pass(), philo->philo_id, msg);
	// pthread_mutex_unlock(&philo->table->start_sim_mutex);
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

//todo: check if gettimeofday faied then clean everything
//* get the current time in milliseconds
long	get_time_ms(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL); 
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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
