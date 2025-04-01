/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:51:25 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 10:27:31 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**free_list(char **list)
{
	int	i;

	i = 0;
	if (!list)
		return (NULL);
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}
