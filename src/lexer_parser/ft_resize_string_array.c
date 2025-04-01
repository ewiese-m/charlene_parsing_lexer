/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resize_string_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:01:42 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 15:23:03 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_resize_string_array(char **array, int current_size,
		int target_size)
{
	char	**new_array;
	int		i;

	new_array = (char **)ft_calloc(target_size, sizeof(char *));
	i = 0;
	while (i < current_size)
	{
		new_array[i] = ft_strdup(array[i]);
		free(array[i]);
		i++;
	}
	free(array);
	return (new_array);
}
