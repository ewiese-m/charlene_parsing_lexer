/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:29 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/07 13:40:09 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**init_cmd_table(int capacity)
{
	char	**cmd_table;

	cmd_table = (char **)ft_calloc(capacity, sizeof(char *));
	return (cmd_table);
}

static void	handle_redirection(char *line, int *i, char **cmd_table, int *count)
{
	int	start;

	start = *i;
	if ((line[*i] == '>' && line[*i + 1] == '>') || (line[*i] == '<' && line[*i
			+ 1] == '<'))
	{
		cmd_table[*count] = ft_substr(line, start, 2);
		*i += 2;
	}
	else
	{
		cmd_table[*count] = ft_substr(line, start, 1);
		(*i)++;
	}
	while (line[*i] == ' ' || (line[*i] >= '\t' && line[*i] <= '\r'))
		(*i)++;
	if (line[*i] && line[*i] != '<' && line[*i] != '>')
	{
		(*count)++;
		cmd_table[*count] = ft_strdup("");
		cmd_table[*count] = ft_tokenize(cmd_table[*count], line, i,
				(t_env *)cmd_table[0]);
	}
}

static void	process_regular_token(char *line, int *i, char **cmd_table,
		int *count)
{
	cmd_table[*count] = ft_strdup("");
	if (cmd_table[*count])
		cmd_table[*count] = ft_tokenize(cmd_table[*count], line, i,
				(t_env *)cmd_table[0]);
}

static char	**resize_cmd_table(char **cmd_table, int *count, int *capacity)
{
	if (cmd_table[*count])
	{
		if (++(*count) >= *capacity - 1)
		{
			*capacity = *capacity * 2;
			cmd_table = ft_realloc(cmd_table, *capacity * sizeof(char *));
		}
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

	capacity = 10;
	count = 1;
	i = 0;
	if (!line)
		return (NULL);
	cmd_table = init_cmd_table(capacity);
	if (!cmd_table)
		return (NULL);
	cmd_table[0] = (char *)env_list;
	while (line[i])
	{
		while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
			i++;
		if (!line[i])
			break ;
		if (line[i] == '<' || line[i] == '>')
		{
			handle_redirection(line, &i, cmd_table, &count);
		}
		else
		{
			process_regular_token(line, &i, cmd_table, &count);
		}
		cmd_table = resize_cmd_table(cmd_table, &count, &capacity);
	}
	cmd_table[count] = NULL;
	return (cmd_table);
}
