/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:17:04 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/10 13:10:56 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*skip_leading_whitespace(char *line)
{
	int	token_count;
	//char *original = line;

	printf("\033[1;37mDEBUG: skip_leading_whitespace called with line = '%s'\033[0m\n",
	       line ? line : "NULL");

	token_count = 0;
	while ((line[token_count] && line[token_count] >= 9
			&& line[token_count] <= 13) || line[token_count] == ' ')
		token_count++;

	if (token_count > 0)
		printf("\033[1;37mDEBUG: Skipped %d leading whitespace characters\033[0m\n", token_count);

	return (&line[token_count]);
}

static int	is_valid_cmd(t_command *cmd)
{
	printf("\033[1;37mDEBUG: is_valid_cmd called\033[0m\n");

	if (cmd->command == NULL)
	{
		printf("\033[1;37mDEBUG: Command is NULL, invalid\033[0m\n");
		return (0);
	}

	if (strlen(cmd->command) == 0)
	{
		printf("\033[1;37mDEBUG: Command is empty, invalid\033[0m\n");
		return (0);
	}

	if (ft_checkforgarbage(cmd))
	{
		printf("\033[1;37mDEBUG: Command contains garbage, invalid\033[0m\n");
		return (0);
	}

	printf("\033[1;37mDEBUG: Command is valid\033[0m\n");
	return (1);
}

static void	clean_and_prepare_cmd(t_command *cmd)
{
	printf("\033[1;37mDEBUG: clean_and_prepare_cmd called\033[0m\n");

	printf("\033[1;37mDEBUG: Removing surplus spaces\033[0m\n");
	ft_removesurplusspaces(cmd);

	printf("\033[1;37mDEBUG: Creating full command array\033[0m\n");
	ft_create_fullcmd(cmd);

	printf("\033[1;37mDEBUG: Command preparation complete\033[0m\n");
}

static t_command	*handle_parse_error(char *line)
{
	printf("\033[1;37mDEBUG: handle_parse_error called with line = '%s'\033[0m\n",
	       line ? line : "NULL");

	printf("minishell: syntax error near unexpected token `%s'\n", line);
	return (NULL);
}

t_command	*ft_parse_input(char *line, t_env *env_list)
{
	t_command	*cmd;
	char		*line_copy;
	char		*trimmed_line;

	printf("\033[1;37mDEBUG: ft_parse_input called with line = '%s'\033[0m\n",
	       line ? line : "NULL");

	line_copy = ft_strdup(line);
	if (!line_copy)
	{
		printf("\033[1;37mDEBUG: Failed to duplicate line\033[0m\n");
		return (NULL);
	}

	printf("\033[1;37mDEBUG: Trimming leading whitespace\033[0m\n");
	trimmed_line = skip_leading_whitespace(line_copy);

	if (*trimmed_line == '\0')
	{
		printf("\033[1;37mDEBUG: Line is empty after trimming\033[0m\n");
		free(line_copy);
		return (NULL);
	}

	printf("\033[1;37mDEBUG: Tokenizing and parsing commands\033[0m\n");
	cmd = tokenize_parse_and_link_commands(trimmed_line, env_list);

	free(line_copy);

	if (!cmd)
	{
		printf("\033[1;37mDEBUG: Command parsing failed\033[0m\n");
		return (handle_parse_error(line));
	}

	printf("\033[1;37mDEBUG: Checking if command is valid\033[0m\n");
	if (!is_valid_cmd(cmd))
	{
		printf("\033[1;37mDEBUG: Command is invalid, freeing\033[0m\n");
		ft_free_cmdlist(&cmd);
		return (NULL);
	}

	printf("\033[1;37mDEBUG: Cleaning and preparing command\033[0m\n");
	clean_and_prepare_cmd(cmd);

	printf("\033[1;37mDEBUG: ft_parse_input returning successfully\033[0m\n");
	return (cmd);
}
