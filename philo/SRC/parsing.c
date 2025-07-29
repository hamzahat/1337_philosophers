/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza_hat <hamza_hat@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:25:37 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/07/29 16:02:52 by hamza_hat        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_header.h"

int	parse_intput(int ac, char *av[], t_table *table)
{
	//todo: check if number of argument is correct! (ac == 5 || ac == 6). if not print an usage example and return from the programe
	if (ac !=5 && ac != 6)
	{
		ft_putstr_fd(2, "Error: wrong number of arguments\n");
		return (1);
	}
	

	//todo: convert all the argv[] to int numbers
	//todo: check if arguments are just numbers not alpha
	//todo: skip all white spaces at the begining
	//todo: skip '+' signe at the begining
	//todo: if we found '-'signe == error
	//todo: check if numbers are < INT_MAX
	//todo: check if number of philosophers == 0
	//todo: handle if number of philosophers == 1
	//todo: timestamps > 60ms
	//todo: philosophers number <= 200
	return (0);
}

/*
 * input example:
 * ./philo 5 800 300 300 4
 * ./philo ==> program_name
 * 5       ==> The number of philosophers and also the number of forks.
 * 800     ==> time_to_die (in milliseconds)
 * 300     ==> time_to_eat (in milliseconds)
 * 300     ==> time_to_sleep (in milliseconds)
 * 4       ==> number_of_times_each_philosopher_must_eat (optional argument)
*/
