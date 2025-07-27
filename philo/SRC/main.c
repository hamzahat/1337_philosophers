/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:22:49 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/07/27 20:22:03 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_header.h"

int main(int ac, char *av[])
{
	t_table	table;
	parse_intput(ac, av); //todo parse input
	fork_init(&table);    //todo initialize fork()
	philos_init();  //todo initialize philo()
	philo_dining(); //todo philosophers dining
	data_clean_up();     //todo clean memory resources!
	return (0);
}
