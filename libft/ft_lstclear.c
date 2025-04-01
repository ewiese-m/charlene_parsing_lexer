/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:58:48 by ewiese-m          #+#    #+#             */
/*   Updated: 2024/10/29 00:39:19 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		lst_tmp = (*lst)->next;
		lstdelone(*lst, del);
		*lst = lst_tmp;
	}
	free(*lst);
	*lst = NULL;
}
