/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:52:16 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:33:15 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_get_envp(char **envp)
{
	int		count;
	t_env	*head;
	t_env	*current;

	count = 0;
	head = ft_create_env_node(envp[count], count);
	if (!head)
		return (NULL);
	current = head;
	while (envp[++count])
	{
		current->next = ft_create_env_node(envp[count], count);
		if (!current->next)
			return (NULL);
		current = current->next;
	}
	return (head);
}
