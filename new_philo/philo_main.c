/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:03 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/08/14 18:29:52 by hbenmoha         ###   ########.fr       */
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


//todo: handke if something failed!
//todo: inside philo_eat every time you try to print someting ( ft_print it check if simulation failed ) so if simulation finished return a specific number then check this number in philo_eat if it mean that simulation failed then lock the locked mtx
//? why you do the monitor as a single thread and not make the main thread as monitor
//todo: fix parsing error => accept just the clean numbers ( 123abc => is not valide )
//todo: go and check the last part of video of oceano when he talk about time to eat should be time to die * 2 to let philo live
//todo: read about pthread_detach .. 
//todo: what are silbiyat dyal treads
//todo: what is zombi thread
//todo: remove the debuggin messages! + falgs from makefile
/*
todo: why we use pthread_join ( answer => to free the stack of the thread) 
todo: but we can use wait  to wait for a thread and the stack will not give as a leak,
todo: because the stack_area of thread was in stack not heap,
todo: so when the int main exit it free all the vars ( memory ), 
todo: but the problem happen when the main thread exit befor the other threads finish so it give as a leak,
todo: so pthread_join want for the thread until it finish,
todo: so it let the main thread to free anything ( stack ) => no leak 
todo: (so that's why the pthread_join fun does not free memeory of thead it just want for it and let main to free everyting )
*/
