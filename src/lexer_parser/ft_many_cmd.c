/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_many_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:19:39 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:33:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_command	*find_last_cmd(t_command *cmd)
{
	t_command	*tail;

	tail = cmd;
	while (tail->next)
		tail = tail->next;
	return (tail);
}

static char	*trim_cmd_start(char *cmd_str)
{
	while (*cmd_str && (*cmd_str == ' ' || *cmd_str == '\t'))
		cmd_str++;
	return (cmd_str);
}

static t_command	*parse_next_command(char *cmd_str, t_env *env_list)
{
	return (ft_parser(ft_lexer(cmd_str, env_list)));
}

static int	add_command_to_list(t_command **head, t_command **tail,
		t_command *next_cmd)
{
	if (!next_cmd)
	{
		ft_free_cmdlist(head);
		return (0);
	}
	(*tail)->next = next_cmd;
	*tail = next_cmd;
	return (1);
}

t_command	*ft_many_cmd(t_command *cmd, char **full_cmd, t_env *env_list)
{
	t_command	*head;
	t_command	*tail;
	char		*cmd_start;

	if (!cmd || !full_cmd)
		return (NULL);
	head = cmd;
	tail = find_last_cmd(cmd);
	while (*full_cmd)
	{
		cmd_start = trim_cmd_start(*full_cmd);
		if (*cmd_start == '\0')
		{
			full_cmd++;
			continue ;
		}
		if (!add_command_to_list(&head, &tail, parse_next_command(cmd_start,
					env_list)))
			return (NULL);
		full_cmd++;
	}
	return (head);
}
