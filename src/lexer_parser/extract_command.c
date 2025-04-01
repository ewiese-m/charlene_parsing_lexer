/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:20:31 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:33:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	extract_command(char *line, int i, char **cmd)
{
	int		start;
	char	quote;
	int		cmd_len;

	start = i;
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
		}
		i++;
	}
	cmd_len = i - start;
	*cmd = malloc(sizeof(char) * (cmd_len + 1));
	if (*cmd)
	{
		memcpy(*cmd, line + start, cmd_len);
		(*cmd)[cmd_len] = '\0';
	}
	return (i);
}
