/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:21:13 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/07/27 20:15:46 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_header.h"

void    forks_init(t_table *table)
{
    int i;

    i = 0;
    table->forks_arr = malloc(sizeof(pthread_mutex_t) * table->philo_nb);
    while (i < table->philo_nb)
    {
        pthread_mutex_init(&table->forks_arr[i], NULL);
        i++;
    }
    
    
}

void    philos_init(t_table *table)
{
    table->philos_arr = malloc(sizeof(t_philo) * table->philo_nb);
}

int	parse_intput(int ac, char *av[])
{
	//todo: check if number of argument is correct! (ac == 5 || ac == 6). if not print an usage example and return from the programe (exit)
	
	return (0);
}
