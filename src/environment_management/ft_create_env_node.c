/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:51:55 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:56:35 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_create_env_node(char *envp, int index)
{
	t_env	*node;
	char	**str;

	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	str = ft_split(envp, '=');
	node->key = ft_strdup(str[0]);
	if (str[1])
		node->value = ft_strdup(str[1]);
	else
		node->value = ft_strdup("");
	node->index = index;
	free_list(str);
	return (node);
}
