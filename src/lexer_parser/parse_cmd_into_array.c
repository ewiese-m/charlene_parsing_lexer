/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_into_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:20:21 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:33:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**parse_cmd_into_array(char *line)
{
	int		cmd_count;
	char	**cmd_array;
	int		cmd_index;
	int		i;

	if (line == NULL)
		return (NULL);
	cmd_count = count_command(line);
	cmd_array = malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmd_array)
		return (NULL);
	cmd_index = 0;
	i = 0;
	while (line[i] && cmd_index < cmd_count)
	{
		i = extract_command(line, i, &cmd_array[cmd_index]);
		if (!cmd_array[cmd_index])
			return (free_list(cmd_array));
		cmd_index++;
		if (line[i] == '|')
			i++;
	}
	cmd_array[cmd_index] = NULL;
	return (cmd_array);
}
