/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:06:36 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/07/30 12:05:45 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//todo: remve exit fun form your ft_safe_malloc garbage collector!

#include "../philo_header.h"

//? Zero out a block of memory.
static void	ft_bzero(void *s, size_t len)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	while (len--)
		*tmp++ = 0;
}

//? Free all allocated memory in the memory tracking list
static void	free_mem_list(t_mem_node **list)
{
	t_mem_node	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->address);
		free(*list);
		*list = tmp;
	}
}

//? Add a new memory block to the memory tracking list.
static int	lst_add_back_malloc(t_mem_node **lst, void *value)
{
	t_mem_node	*last;
	t_mem_node	*tmp;

	if (!lst || !value)
		return (1);
	tmp = malloc(sizeof(t_mem_node));
	if (!tmp)
		return (free_mem_list(lst), 1);
	tmp->address = value;
	tmp->next = NULL;
	if (!*lst)
	{
		*lst = tmp;
		return (0);
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = tmp;
	return (0);
}

//? Free a specific memory block and update the tracking list
static void	free_specific_node(t_mem_node **lst, void *to_delete)
{
	t_mem_node	*current;
	t_mem_node	*prev;

	if (!lst || !to_delete)
		return ;
	current = *lst;
	prev = NULL;
	while (current)
	{
		if (current->address == to_delete)
		{
			free(current->address);
			if (prev)
				prev->next = current->next;
			else
				*lst = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	free(to_delete);
}

//? Allocate memory, track it, and handle failures safely.
void	*ft_safe_malloc(size_t size, int key, void *to_delete)
{
	static t_mem_node	*mem_node;
	void				*ptr;

	ptr = NULL;
	if (key == ALLOCATE)
	{
		ptr = malloc(size);
		if (!ptr)
			return (free_mem_list(&mem_node), NULL);
		if (lst_add_back_malloc(&mem_node, ptr) == 1)
			return (NULL);
		ft_bzero(ptr, size);
	}
	else if (key == FREE_ALL)
		free_mem_list(&mem_node);
	else if (key == FREE_ONE)
		free_specific_node(&mem_node, to_delete);
	return (ptr);
}
