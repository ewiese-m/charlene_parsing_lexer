/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrange_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:24:53 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:33:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_arrange_table(char **table, int index, int len)
{
	if (table[index][len] == '\0')
	{
		free(table[index]);
		free(table[index + 1]);
		while (table[index + 2])
		{
			table[index] = table[index + 2];
			index++;
		}
		table[index] = NULL;
		return ;
	}
	free(table[index]);
	table[index] = table[index + 1];
	while (table[++index])
		table[index] = table[index + 1];
}
