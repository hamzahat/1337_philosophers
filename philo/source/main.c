/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:22:49 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/02 09:44:54 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_header.h"

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

//todo: initialize philos (in progress)
	if (philos_init(&table))
		return (ft_safe_malloc(0, FREE_ALL, NULL), 1);

//todo: philosophers dining
	// philo_dining_start();

//todo clean memory resources!

	return (0);
}

//? if a thread_init faild we should free the old threads (pthread_mutex_destroy()) !?