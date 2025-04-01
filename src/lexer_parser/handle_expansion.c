/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:29:36 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 15:04:15 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_expansion(char *result, char *input, int *i, t_env *env_list)
{
	int		var_pos;
	char	*expanded;
	char	*old;

	var_pos = *i;
	expanded = ft_extract_env_var(input, &var_pos, env_list);
	old = result;
	result = ft_strjoin(result, expanded);
	free(old);
	free(expanded);
	*i = var_pos + 1;
	return (result);
}
