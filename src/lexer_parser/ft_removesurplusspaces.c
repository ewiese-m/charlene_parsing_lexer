/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_removesurplusspaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:43:31 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:33:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_removesurplusspaces(t_command *cmd)
{
	t_command	*tmp;
	int			count;
	char		*new_str;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->command)
			return ;
		count = 0;
		while (!ft_isascii(tmp->command[count]) || tmp->command[count] == ' '
			|| tmp->command[count] == '\t' || tmp->command[count] == '\v')
			count++;
		if (count)
		{
			new_str = ft_strdup(&tmp->command[count]);
			free(tmp->command);
			tmp->command = new_str;
		}
		tmp = tmp->next;
	}
}
