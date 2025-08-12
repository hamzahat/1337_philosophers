/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:25:37 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/12 18:26:49 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

//? converte argv to valide numbers
static int	convert_args_to_nb(t_table *table, char *av[])
{
	if (!table)
		return (1);
	if ((table->philo_nb = ft_atoi(av[1])) == -1 || table->philo_nb == 0 || table->philo_nb > 200)
		return (ft_putstr_fd(2, "Error: number_of_philosophers is not correct!\n"), 1);
	if ((table->time_to_die = ft_atoi(av[2])) == -1 || table->time_to_die <= 60)
		return (ft_putstr_fd(2, "Error: time_to_die is not correct!\n"), 1);
	if ((table->time_to_eat = ft_atoi(av[3])) == -1 || table->time_to_eat <= 60)
		return (ft_putstr_fd(2, "Error: time_to_eat is not correct!\n"), 1);
	if ((table->time_to_sleep = ft_atoi(av[4])) == -1 || table->time_to_sleep <= 60)
		return (ft_putstr_fd(2, "Error: time_to_sleep is not correct!\n"), 1);
	if (av[5])
		if ((table->meals_nb = ft_atoi(av[5])) == -1 || table->meals_nb < 1)
			return (ft_putstr_fd(2, "Error: number_of_times_each_philosopher_must_eat is not correct!\n"), 1);
	return (0);
}

//? check if argc number is correct! (5 || 6)
static int	check_args_number(int ac)
{
	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd(2, "Error: wrong number of arguments\n");
		return (1);
	}
	return (0);
}

//? main function of arguments parsing
int	parse_input(int ac, char *av[], t_table *table)
{
	if (check_args_number(ac)) //* done
		return (1);
	if (initialize_table_data(table)) //* done
		return (1);
	if (allocate_philos_arr(table)) //* done
		return (1);
	if (allocate_forks_arr(table)) //* done
		return (1);
	if (convert_args_to_nb(table, av)) //* done
		return (1);
	return (0);
}
