/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:03 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/13 15:16:25 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int	main(int ac, char *av[])
{
	t_table	table;

	if (parse_input(ac, av))
		return (1);
	if (data_init(av, &table))
		return (1);
	// print_data_debugging(&table);
	//todo: dining start
	if(dining_start(&table))
		return (1);
	//todo: clean up
	return (0);
}
