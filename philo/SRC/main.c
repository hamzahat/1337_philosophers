/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza_hat <hamza_hat@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:22:49 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/07/29 13:12:40 by hamza_hat        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_header.h"

int main(int ac, char *av[])
{
	t_table	table;
	if (parse_intput(ac, av, &table)) //todo parse input
		return (1);
	// fork_init(&table);    //todo initialize fork()
	// philos_init();  //todo initialize philo()
	// philo_dining(); //todo philosophers dining
	// data_clean_up();     //todo clean memory resources!
	return (0);
}
