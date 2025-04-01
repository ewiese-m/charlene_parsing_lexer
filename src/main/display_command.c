/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:30:00 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:41:36 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_command_info(t_command *cmds)
{
	t_command	*current;
	int			cmd_count;
	char		*has_next;

	current = cmds;
	cmd_count = 1;
	while (current)
	{
		printf("\n==== Command %d ====\n", cmd_count++);
		display_command_name(current);
		display_arguments(current);
		display_full_command(current);
		display_redirections(current);
		current = current->next;
		has_next = "No";
		if (current)
			has_next = "Yes";
		printf("Has next command: %s\n", has_next);
	}
}
