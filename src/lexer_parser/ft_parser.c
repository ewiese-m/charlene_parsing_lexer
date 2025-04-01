/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:21:11 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/30 15:13:43 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_command	*init_cmd_struct(void)
{
	t_command	*cmd;

	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	return (cmd);
}

static int	allocate_args_array(t_command *cmd, char **cmd_table, int start_idx)
{
	int	arg_count;

	arg_count = 0;
	while (cmd_table[start_idx + arg_count])
		arg_count++;
	cmd->args = (char **)ft_calloc(arg_count + 1, sizeof(char *));
	if (!cmd->args)
		return (0);
	return (1);
}

static void	copy_args_to_cmd(t_command *cmd, char **cmd_table, int start_idx)
{
	int	i;
	int	j;

	i = start_idx;
	j = 0;
	while (cmd_table[i])
	{
		cmd->args[j] = ft_strdup(cmd_table[i]);
		i++;
		j++;
	}
	cmd->args[j] = NULL;
}

static int	setup_command(t_command *cmd, char **cmd_table)
{
	int	start_idx;

	start_idx = 1;
	if (ft_check_redirect(cmd, &cmd_table[start_idx]))
		return (0);
	if (cmd_table[start_idx])
	{
		cmd->command = ft_strdup(cmd_table[start_idx]);
	}
	else
	{
		return (0);
	}
	if (!allocate_args_array(cmd, cmd_table, start_idx))
	{
		free(cmd->command);
		return (0);
	}
	copy_args_to_cmd(cmd, cmd_table, start_idx);
	return (1);
}

t_command	*ft_parser(char **cmd_table)
{
	t_command	*cmd;
	int			i;

	i = 1;
	if (!cmd_table)
	{
		return (NULL);
	}
	cmd = init_cmd_struct();
	if (!cmd)
	{
		return (NULL);
	}
	if (!setup_command(cmd, cmd_table))
	{
		free(cmd);
		return (NULL);
	}
	while (cmd_table[i])
	{
		free(cmd_table[i]);
		i++;
	}
	free(cmd_table);
	return (cmd);
}
