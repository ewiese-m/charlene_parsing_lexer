/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:16:26 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 15:16:30 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_expand_variable(char *str, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	if (!str)
		return (ft_strdup("$"));
	if (!ft_strcmp(str, "?"))
	{
		free(str);
		return (ft_itoa(env_list->exit_status));
	}
	while (current)
	{
		if (!ft_strcmp(str, current->key))
		{
			free(str);
			if (!env_list->custom && !current->value)
				return (ft_strdup("\n"));
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	free(str);
	return (ft_strdup(""));
}
