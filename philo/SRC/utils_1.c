/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:21:13 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/07/26 21:33:48 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_header.h"

void    fork_init(t_table *table)
{
    int i;

    i = 0;
    table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nb);
    while (i < table->philo_nb)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
    
    
}

void    philos_init(t_table *table)
{
    table->philos_arr = malloc(sizeof(t_philos) * table->philo_nb);
}
