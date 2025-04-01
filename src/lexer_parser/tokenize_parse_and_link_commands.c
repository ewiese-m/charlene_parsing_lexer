/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_parse_and_link_commands.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:19:09 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/03/29 09:33:32 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*tokenize_parse_and_link_commands(char *line, t_env *env_list)
{
	char		**full_cmd_array;
	t_command	*cmd;
	int			count;
	int			len;

	count = 0;
	len = 0;
	full_cmd_array = parse_cmd_into_array(line);
	if (!full_cmd_array)
		return (NULL);
	while (full_cmd_array[len])
		len++;
	cmd = ft_parser(ft_lexer(full_cmd_array[count], env_list));
	if (len > 1)
		cmd = ft_many_cmd(cmd, &full_cmd_array[1], env_list);
	ft_free_dstr(full_cmd_array);
	return (cmd);
}
