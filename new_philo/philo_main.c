/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:03 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/14 22:10:19 by hbenmoha         ###   ########.fr       */
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
	if(dining_start(&table))
		return (clean_up(&table), 1);
	clean_up(&table);
	return (0);
}


//todo: add check in parsing of philo_nbr < 200 timestapms > 60
//todo: handke if something failed!

//? why you do the monitor as a single thread and not make the main thread as monitor
//todo: go and check the last part of video of oceano when he talk about time to eat should be time to die * 2 to let philo live
//todo: read about pthread_detach .. 
//todo: what are silbiyat dyal treads
//todo: what is zombi thread
//todo: remove the debuggin messages! + falgs from makefile
/*
 why we use pthread_join ( answer => to free the stack of the thread) 
 but we can use wait  to wait for a thread and the stack will not give as a leak,
 because the stack_area of thread was in stack not heap,
 so when the int main exit it free all the vars ( memory ), 
 but the problem happen when the main thread exit befor the other threads finish so it give as a leak,
 so pthread_join want for the thread until it finish,
 so it let the main thread to free anything ( stack ) => no leak 
 (so that's why the pthread_join fun does not free memeory of thead it just want for it and let main to free everyting )
*/
