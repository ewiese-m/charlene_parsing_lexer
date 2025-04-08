/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:16:26 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 18:10:47 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_null_var(void)
{
	return (ft_strdup("$"));
}

static char	*handle_question_mark(char *str, t_env *env_list)
{
	t_env	*current;

	free(str);
	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "?") == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup("0"));
}

static char	*handle_exit_status(char *str, t_env *env_list)
{
	free(str);
	return (ft_itoa(env_list->exit_status));
}

static char	*handle_env_variable(char *str, t_env *env_list)
{
	t_env	*current;
	char	*value;

	current = env_list;
	while (current)
	{
		if (!ft_strcmp(str, current->key))
		{
			free(str);
			if (!env_list->custom && !current->value)
				value = ft_strdup("\n");
			else
				value = ft_strdup(current->value);
			return (value);
		}
		current = current->next;
	}
	free(str);
	return (ft_strdup(""));
}

char	*ft_expand_variable(char *str, t_env *env_list)
{
	if (!str)
		return (handle_null_var());
	if (ft_strcmp(str, "?") == 0)
		return (handle_question_mark(str, env_list));
	if (!ft_strcmp(str, "?"))
		return (handle_exit_status(str, env_list));
	return (handle_env_variable(str, env_list));
}
