/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:29 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/10 13:09:09 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**init_cmd_table(int capacity)
{
	char	**cmd_table;

	printf("\033[36mDEBUG: init_cmd_table called with capacity = %d\033[0m\n", capacity);
	cmd_table = (char **)ft_calloc(capacity, sizeof(char *));

	if (!cmd_table)
		printf("\033[36mDEBUG: Failed to allocate cmd_table\033[0m\n");
	else
		printf("\033[36mDEBUG: cmd_table allocated successfully\033[0m\n");

	return (cmd_table);
}

static void	handle_redirection(char *line, int *i, char **cmd_table, int *count)
{
	int	start;

	printf("\033[36mDEBUG: handle_redirection called at position %d with char '%c'\033[0m\n",
	       *i, line[*i]);

	start = *i;
	if ((line[*i] == '>' && line[*i + 1] == '>') || (line[*i] == '<' && line[*i
			+ 1] == '<'))
	{
		printf("\033[36mDEBUG: Found double redirection: %c%c\033[0m\n", line[*i], line[*i+1]);
		cmd_table[*count] = ft_substr(line, start, 2);
		*i += 2;
	}
	else
	{
		printf("\033[36mDEBUG: Found single redirection: %c\033[0m\n", line[*i]);
		cmd_table[*count] = ft_substr(line, start, 1);
		(*i)++;
	}

	printf("\033[36mDEBUG: Redirection token: '%s'\033[0m\n", cmd_table[*count]);

	while (line[*i] == ' ' || (line[*i] >= '\t' && line[*i] <= '\r'))
		(*i)++;

	if (line[*i] && line[*i] != '<' && line[*i] != '>')
	{
		printf("\033[36mDEBUG: Found redirection target at position %d\033[0m\n", *i);
		(*count)++;
		cmd_table[*count] = ft_strdup("");
		cmd_table[*count] = ft_tokenize(cmd_table[*count], line, i,
				(t_env *)cmd_table[0]);
		printf("\033[36mDEBUG: Redirection target token: '%s'\033[0m\n", cmd_table[*count]);
	}
	else
	{
		printf("\033[36mDEBUG: No immediate redirection target found\033[0m\n");
	}
}

static void	process_regular_token(char *line, int *i, char **cmd_table,
		int *count)
{
	printf("\033[36mDEBUG: process_regular_token called at position %d\033[0m\n", *i);

	cmd_table[*count] = ft_strdup("");
	if (cmd_table[*count])
	{
		cmd_table[*count] = ft_tokenize(cmd_table[*count], line, i,
				(t_env *)cmd_table[0]);
		printf("\033[36mDEBUG: Regular token: '%s', new position: %d\033[0m\n",
		       cmd_table[*count], *i);
	}
	else
	{
		printf("\033[36mDEBUG: Failed to initialize token string\033[0m\n");
	}
}

static char	**resize_cmd_table(char **cmd_table, int *count, int *capacity)
{
	char **new_table;

	if (cmd_table[*count])
	{
		if (++(*count) >= *capacity - 1)
		{
			printf("\033[36mDEBUG: Resizing cmd_table from %d to %d\033[0m\n",
			       *capacity, *capacity * 2);

			*capacity = *capacity * 2;
			new_table = ft_realloc(cmd_table, *capacity * sizeof(char *));

			if (new_table != cmd_table)
				printf("\033[36mDEBUG: cmd_table relocated during resize\033[0m\n");

			return new_table;
		}
	}
	else
	{
		printf("\033[36mDEBUG: Token at index %d is NULL, not incrementing count\033[0m\n",
		       *count);
	}
	return (cmd_table);
}

// Mantener env_list en cmd_table[0]
// cmd_table[0] = NULL; // NO BORRAR env_list
// Comenzamos en 1 porque 0 es para env_list
char	**ft_lexer(char *line, t_env *env_list)
{
	char	**cmd_table;
	int		count;
	int		i;
	int		capacity;

	printf("\033[36mDEBUG: ft_lexer called with line = '%s'\033[0m\n", line ? line : "NULL");

	capacity = 10;
	count = 1;
	i = 0;

	if (!line)
	{
		printf("\033[36mDEBUG: line is NULL, returning NULL\033[0m\n");
		return (NULL);
	}

	cmd_table = init_cmd_table(capacity);
	if (!cmd_table)
	{
		printf("\033[36mDEBUG: Failed to initialize cmd_table\033[0m\n");
		return (NULL);
	}

	printf("\033[36mDEBUG: Storing env_list pointer in cmd_table[0]\033[0m\n");
	cmd_table[0] = (char *)env_list;

	printf("\033[36mDEBUG: Starting tokenization loop\033[0m\n");
	while (line[i])
	{
		// Skip whitespace
		while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
			i++;

		if (!line[i])
		{
			printf("\033[36mDEBUG: Reached end of line after whitespace\033[0m\n");
			break;
		}

		printf("\033[36mDEBUG: Processing token starting at position %d ('%c')\033[0m\n",
		       i, line[i]);

		if (line[i] == '<' || line[i] == '>')
		{
			printf("\033[36mDEBUG: Found redirection character\033[0m\n");
			handle_redirection(line, &i, cmd_table, &count);
		}
		else
		{
			printf("\033[36mDEBUG: Found regular token\033[0m\n");
			process_regular_token(line, &i, cmd_table, &count);
		}

		cmd_table = resize_cmd_table(cmd_table, &count, &capacity);
		printf("\033[36mDEBUG: Current token count: %d\033[0m\n", count);
	}

	printf("\033[36mDEBUG: Tokenization completed, setting cmd_table[%d] = NULL\033[0m\n", count);
	cmd_table[count] = NULL;

	printf("\033[36mDEBUG: ft_lexer returning with %d tokens\033[0m\n", count);
	return (cmd_table);
}
