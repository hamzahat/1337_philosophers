/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:42:18 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/15 12:06:25 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	parse_input(int ac, char *av[])
{
	int	philo_nb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_nbr;

	philo_nb = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	meals_nbr = ft_atoi(av[5]);
	if (ac != 5 && ac != 6)
		return (ft_putstr_fd(2, "Error: wrong number of arguments\n"), 1);
	if (philo_nb < 1 || philo_nb > 200)
		return (ft_putstr_fd(2, "Error: "N_OF_PHILO" is not correct!\n"), 1);
	if (time_to_die < 1 || time_to_die < 60)
		return (ft_putstr_fd(2, "Error: time_to_die is not correct!\n"), 1);
	if (time_to_eat < 1 || time_to_eat < 60)
		return (ft_putstr_fd(2, "Error: time_to_eat is not correct!\n"), 1);
	if (time_to_sleep < 1 || time_to_sleep < 60)
		return (ft_putstr_fd(2, "Error: time_to_sleep is not correct!\n"), 1);
	if (av[5] && meals_nbr < 1)
		return (ft_putstr_fd(2, "Error: "N_OF_MEALS" is not correct!\n"), 1);
	return (0);
}
