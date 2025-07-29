/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza_hat <hamza_hat@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:57:14 by hamza_hat         #+#    #+#             */
/*   Updated: 2025/07/29 12:57:50 by hamza_hat        ###   ########.fr       */
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
