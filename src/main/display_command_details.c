/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_command_details.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:30:00 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:31:06 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_command_name(t_command *cmd)
{
	if (cmd->command)
		printf("Command: %s\n", cmd->command);
	else
		printf("Command: NULL\n");
}

void	display_arguments(t_command *cmd)
{
	int	arg_idx;

	printf("Arguments: ");
	if (cmd->args)
	{
		arg_idx = 0;
		while (cmd->args[arg_idx])
		{
			printf("[%s] ", cmd->args[arg_idx]);
			arg_idx++;
		}
		printf("\n");
	}
	else
		printf("NULL\n");
}

void	display_full_command(t_command *cmd)
{
	int	cmd_idx;

	printf("Full Command: ");
	if (cmd->full_cmd)
	{
		cmd_idx = 0;
		while (cmd->full_cmd[cmd_idx])
		{
			printf("[%s] ", cmd->full_cmd[cmd_idx]);
			cmd_idx++;
		}
		printf("\n");
	}
	else
		printf("NULL\n");
}
