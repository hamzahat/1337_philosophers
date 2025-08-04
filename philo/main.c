/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:22:49 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/04 16:57:21 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int main(int ac, char *av[])
{
	t_table	table;

//* parse input:
	if (parse_intput(ac, av, &table))
		return (ft_safe_malloc(0, FREE_ALL, NULL), 1);
//* print t_table data:
	printf_input_data(table);

//* initialize froks (mutex + fork_id):
	if (forks_init(&table))
		return (ft_safe_malloc(0, FREE_ALL, NULL), 1);

//* initialize philos data + assign forks;
	if (philos_init(&table))
		return (ft_safe_malloc(0, FREE_ALL, NULL), 1);

//todo: philosophers dining (in progress)
	if (philo_dining_start(&table))
		return (ft_safe_malloc(0, FREE_ALL, NULL), 1);

//todo clean memory resources!
	clean_up();
	return (0);
}

//? if a thread_init faild we should free the old threads (pthread_mutex_destroy()) !?
//todo: handle if the philo_nb == 0
//! test if we give one philo / fork it will lead to deadlock !? (in assign_forks_to_philos())
