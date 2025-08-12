/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:42:18 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/12 13:40:40 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	parse_input(int ac, char *av[])
{
	if (ac != 5 && ac != 6)
		return (ft_putstr_fd(2, "Error: wrong number of arguments\n"), 1);
	if (ft_atoi(av[1]) < 1)
		return (ft_putstr_fd(2, "Error: number_of_philosophers is not correct!\n"), 1);
	if (ft_atoi(av[2]) < 1)
		return (ft_putstr_fd(2, "Error: time_to_die is not correct!\n"), 1);
	if (ft_atoi(av[3]) < 1)
		return (ft_putstr_fd(2, "Error: time_to_eat is not correct!\n"), 1);
	if (ft_atoi(av[4]) < 1)
		return (ft_putstr_fd(2, "Error: time_to_sleep is not correct!\n"), 1);
	if (av[5] && ft_atoi(av[5]) < 1)
		return (ft_putstr_fd(2, "Error: number_of_times_each_philosopher_must_eat is not correct!\n"), 1);
	return (printf("correct input!\n"), 0); //todo: remove this msg
}
