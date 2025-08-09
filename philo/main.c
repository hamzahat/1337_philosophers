/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:22:49 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/09 13:22:03 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int main(int ac, char *av[])
{
	t_table	table;

//* parse input:
	if (parse_input(ac, av, &table))
		return (ft_safe_malloc(0, FREE_ALL, NULL), 1);

//* print t_table data: (debaging usage)
	printf_input_data(table);

//* init data (mutexs + philos ...)
	if (data_init(&table))
		return (clean_up(&table), 1);

//todo: philosophers dining (in progress)
	if (philo_dining_start(&table))
		return (clean_up(&table), 1);

//todo clean memory resources!
	clean_up(&table);
	return (0);
}

//? if a thread_init faild we should free the old threads (pthread_mutex_destroy()) !?
//todo: handle if the philo number is 1 (first understand the problem then fix it)
//! test if we give one philo / fork it will lead to deadlock !? (in assign_forks_to_philos())
//todo: don't forget to destroy the mutexs

//todo: you should handl if any (failur of memory) or (datat init) you should destroy + free memory resources and join threads
//* hint: initialyze everything to NULL, then befor destroy it check if it's NULL
//* hint: initialyze everything to NULL, then befor destroy it check if it's NULL if you found that it's NULL so it's not initialyzed yet
//? if a thread faile we should do ptrjoin for the other threads or pthread_detach !? (katami dar pthread_join())
