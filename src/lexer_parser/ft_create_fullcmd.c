/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_fullcmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:18:20 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/31 15:38:27 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_fullcmd(t_command *cmd)
{
	int	arg_count;
	int	i;

	while (cmd)
	{
		if (!cmd->command)
			return ;
		arg_count = 0;
		while (cmd->args && cmd->args[arg_count])
			arg_count++;
		cmd->full_cmd = (char **)ft_calloc(arg_count + 2, sizeof(char *));
		if (!cmd->full_cmd)
			return ;
		i = 0;
		while (i < arg_count)
		{
			cmd->full_cmd[i] = ft_strdup(cmd->args[i]);
			i++;
		}
		cmd->full_cmd[i] = NULL;
		if (cmd->next)
			cmd = cmd->next;
		else
			return ;
	}
}
