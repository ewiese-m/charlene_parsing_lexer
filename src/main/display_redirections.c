/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:30:00 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 13:05:29 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	display_input_redirection(t_command *cmd)
{
	if (cmd->from_file)
		printf("Input from file: [%s]\n", cmd->from_file);
	else
		printf("Input from file: None\n");
}

static void	display_heredoc(t_command *cmd)
{
	int	hdoc_idx;

	printf("Heredoc delimiters: ");
	if (cmd->hdocs_end)
	{
		hdoc_idx = 0;
		while (cmd->hdocs_end[hdoc_idx])
		{
			printf("[%s] ", cmd->hdocs_end[hdoc_idx]);
			hdoc_idx++;
		}
		printf("\n");
	}
	else
		printf("None\n");
}

static void	display_output_redirection(t_command *cmd)
{
	int	out_idx;

	printf("Output to files: ");
	if (cmd->to_file)
	{
		out_idx = 0;
		while (cmd->to_file[out_idx])
		{
			printf("[%s] ", cmd->to_file[out_idx]);
			out_idx++;
		}
		printf("\n");
	}
	else
		printf("None\n");
}

static void	display_file_descriptors(t_command *cmd)
{
	printf("Input FD: %d\n", cmd->input);
	printf("Output FD: %d\n", cmd->output);
}

void	display_redirections(t_command *cmd)
{
	printf("Redirect flags: %d\n", cmd->redirect);
	display_input_redirection(cmd);
	display_heredoc(cmd);
	display_output_redirection(cmd);
	display_file_descriptors(cmd);
}
