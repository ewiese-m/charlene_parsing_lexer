/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:24:59 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/10 13:07:57 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_redirect_length(int redirect_type)
{
	int length;

	if (redirect_type & (HEREDOC | APPEND))
		length = 2;
	else
		length = 1;

	printf("\033[34mDEBUG: get_redirect_length for type %d = %d\033[0m\n", redirect_type, length);
	return (length);
}

static int	process_redirection(t_command *cmd, char **cmd_table, int i,
		int redirect_type)
{
	int	redirect_len;
	int	old_redirect;
	int result;

	printf("\033[34mDEBUG: process_redirection called for token '%s', type %d\033[0m\n",
	       cmd_table[i], redirect_type);

	redirect_len = get_redirect_length(redirect_type);
	old_redirect = cmd->redirect;

	printf("\033[34mDEBUG: Setting cmd->redirect from %d to %d\033[0m\n",
	       old_redirect, redirect_type);
	cmd->redirect = redirect_type;

	printf("\033[34mDEBUG: Calling ft_add_redirection\033[0m\n");
	result = ft_add_redirection(cmd_table, cmd, i, redirect_len);
	if (result)
	{
		printf("\033[34mDEBUG: ft_add_redirection failed with error %d\033[0m\n", result);
		return (1);
	}

	printf("\033[34mDEBUG: Updating cmd->redirect to %d | %d = %d\033[0m\n",
	       redirect_type, old_redirect, redirect_type | old_redirect);
	cmd->redirect = redirect_type | old_redirect;

	printf("\033[34mDEBUG: Calling ft_arrange_table\033[0m\n");
	ft_arrange_table(cmd_table, i, redirect_len);

	printf("\033[34mDEBUG: process_redirection completed successfully\033[0m\n");
	return (0);
}

int	ft_check_redirect(t_command *cmd, char **cmd_table)
{
	int	i;
	int	redirect_type;
	int	process_result;

	printf("\033[34mDEBUG: ft_check_redirect called\033[0m\n");

	if (!cmd_table)
	{
		printf("\033[34mDEBUG: cmd_table is NULL\033[0m\n");
		return (0);
	}

	i = 0;
	while (cmd_table[i])
	{
		printf("\033[34mDEBUG: Checking token[%d] = '%s'\033[0m\n", i, cmd_table[i]);

		redirect_type = ft_get_redirection(cmd_table[i]);
		if (redirect_type)
		{
			printf("\033[34mDEBUG: Found redirection token: '%s', type: %d\033[0m\n",
			       cmd_table[i], redirect_type);

			process_result = process_redirection(cmd, cmd_table, i, redirect_type);
			if (process_result)
			{
				printf("\033[34mDEBUG: process_redirection failed\033[0m\n");
				return (1);
			}

			printf("\033[34mDEBUG: After redirection processing, cmd->redirect = %d\033[0m\n",
			       cmd->redirect);
		}
		else
		{
			printf("\033[34mDEBUG: Not a redirection token, moving to next\033[0m\n");
			i++;
		}
	}

	printf("\033[34mDEBUG: ft_check_redirect completed successfully\033[0m\n");
	return (0);
}
