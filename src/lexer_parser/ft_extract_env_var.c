/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:16:52 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 15:21:29 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_extract_env_var(char *input_str, int *pos, t_env *env_list)
{
	char	*var_name;
	int		i;

	i = *pos;
	var_name = NULL;
	while (input_str[++i] && (input_str[i] == '_' || input_str[i] == '?'
			|| ft_isalnum(input_str[i])))
		var_name = ft_concat_and_free(var_name, ft_substr(&input_str[i], 0, 1));
	*pos = i - 1;
	return (ft_expand_variable(var_name, env_list));
}
