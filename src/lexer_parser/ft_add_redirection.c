/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:22:23 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:33:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_add_redirection(char **table, t_command *cmd, int index, int len)
{
	int	count;

	count = 0;
	while (table[index][count] && (table[index][count] == '<'
			|| table[index][count] == '>'))
		count++;
	if (count != len)
		return (printf("syntax error near unexpected token `%c'\n",
				table[index][0]), 1);
	if (table[index][len] == '\0')
	{
		len = 0;
		index++;
		if (table[index] == NULL)
			return (printf("syntax error near unexpected token `newline'\n"),
				1);
	}
	if (cmd->redirect & IN_REDIR)
		cmd->from_file = ft_add_io_file(cmd->from_file, table[index], len);
	else if (cmd->redirect & HEREDOC)
		cmd->hdocs_end = ft_many_redirect(cmd->hdocs_end, table[index], len);
	else
		cmd->to_file = ft_many_redirect(cmd->to_file, table[index], len);
	return (0);
}
