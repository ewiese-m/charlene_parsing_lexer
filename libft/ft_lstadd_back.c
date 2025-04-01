/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:58:39 by ewiese-m          #+#    #+#             */
/*   Updated: 2024/10/25 22:06:03 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != 0)
		current = current->next;
	current->next = new;
}
/*
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*last;

	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	last->next = new;
}
*/
