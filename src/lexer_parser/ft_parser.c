/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:21:11 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/10 20:56:06 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_command	*init_cmd_struct(void)
{
	t_command	*cmd;

	printf("\033[33mDEBUG: init_cmd_struct called\033[0m\n");
	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	if (cmd)
    {
        cmd->command = NULL;
        cmd->args = NULL;
        cmd->full_cmd = NULL;
        cmd->from_file = NULL;  // This already sets it to NULL
        cmd->hdocs_end = NULL;
        cmd->to_file = NULL;
        cmd->redirect = 0;
        cmd->input = 0;
        cmd->output = 0;
        cmd->next = NULL;
    }
	printf("\033[33mDEBUG: Command structure %s\033[0m\n",
	       cmd ? "initialized successfully" : "initialization failed");
	return (cmd);
}

static int	allocate_args_array(t_command *cmd, char **cmd_table, int start_idx)
{
	int	arg_count;

	printf("\033[33mDEBUG: allocate_args_array called with start_idx = %d\033[0m\n", start_idx);
	arg_count = 0;
	while (cmd_table[start_idx + arg_count])
	{
		printf("\033[33mDEBUG: arg[%d] = '%s'\033[0m\n",
		       arg_count, cmd_table[start_idx + arg_count]);
		arg_count++;
	}
	printf("\033[33mDEBUG: Found %d arguments\033[0m\n", arg_count);

	cmd->args = (char **)ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->args)
	{
		printf("\033[33mDEBUG: Failed to allocate args array\033[0m\n");
		return (0);
	}
	printf("\033[33mDEBUG: Args array allocated successfully for %d args\033[0m\n", arg_count);
	return (1);
}

static void	copy_args_to_cmd(t_command *cmd, char **cmd_table, int start_idx)
{
	int	i;
	int	j;

	printf("\033[33mDEBUG: copy_args_to_cmd called with start_idx = %d\033[0m\n", start_idx);
	i = start_idx;
	j = 0;
	while (cmd_table[i])
	{
		cmd->args[j] = ft_strdup(cmd_table[i]);
		printf("\033[33mDEBUG: Copied arg[%d] = '%s'\033[0m\n",
		       j, cmd->args[j] ? cmd->args[j] : "NULL");
		i++;
		j++;
	}
	cmd->args[j] = NULL;
	printf("\033[33mDEBUG: Copied %d arguments\033[0m\n", j);
}

static int	setup_command(t_command *cmd, char **cmd_table)
{
	int	start_idx;

	printf("\033[33mDEBUG: setup_command called\033[0m\n");
	start_idx = 1;
	printf("\033[33mDEBUG: Checking for redirections starting at index %d\033[0m\n", start_idx);

	if (ft_check_redirect(cmd, &cmd_table[start_idx]))
	{
		printf("\033[33mDEBUG: Redirection check failed\033[0m\n");
		return (0);
	}
	printf("\033[33mDEBUG: After redirect check, cmd->redirect = %d\033[0m\n", cmd->redirect);

	if (cmd_table[start_idx])
	{
		printf("\033[33mDEBUG: Setting command to '%s'\033[0m\n", cmd_table[start_idx]);
		cmd->command = ft_strdup(cmd_table[start_idx]);
	}
	else
	{
		printf("\033[33mDEBUG: No command found at index %d\033[0m\n", start_idx);
		return (0);
	}

	if (!allocate_args_array(cmd, cmd_table, start_idx))
	{
		printf("\033[33mDEBUG: Failed to allocate args array\033[0m\n");
		free(cmd->command);
		return (0);
	}

	copy_args_to_cmd(cmd, cmd_table, start_idx);
	printf("\033[33mDEBUG: Command setup complete\033[0m\n");
	return (1);
}

t_command	*ft_parser(char **cmd_table)
{
	t_command	*cmd;
	int			i;

	printf("\033[33mDEBUG: ft_parser called\033[0m\n");
	i = 1;
	if (!cmd_table)
	{
		printf("\033[33mDEBUG: cmd_table is NULL\033[0m\n");
		return (NULL);
	}
	else
	{
		printf("\033[33mDEBUG: cmd_table[0] = %p, cmd_table[1] = %s\033[0m\n",
		       cmd_table[0], cmd_table[1] ? cmd_table[1] : "NULL");
	}

	cmd = init_cmd_struct();
	if (!cmd)
	{
		printf("\033[33mDEBUG: Failed to initialize command structure\033[0m\n");
		return (NULL);
	}

	if (!setup_command(cmd, cmd_table))
	{
		printf("\033[33mDEBUG: Command setup failed\033[0m\n");
		free(cmd);
		return (NULL);
	}

	printf("\033[33mDEBUG: Freeing cmd_table entries\033[0m\n");
	while (cmd_table[i])
	{
		free(cmd_table[i]);
		i++;
	}
	free(cmd_table);

	printf("\033[33mDEBUG: ft_parser returning command: %s\033[0m\n",
	       cmd->command ? cmd->command : "NULL");
	return (cmd);
}
