/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:11 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/10 13:08:21 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_quotes(char *str, char *input, int *i, t_env *env_list)
{
	char *result;
	char quote_type = input[*i];

	printf("\033[32mDEBUG: handle_quotes called at position %d with quote '%c'\033[0m\n",
	       *i, quote_type);

	result = ft_process_quotes(str, input, i, env_list);

	printf("\033[32mDEBUG: handle_quotes returned '%s', new position: %d\033[0m\n",
	       result ? result : "NULL", *i);

	return (result);
}

static char	*handle_dollar_sign(char *str, char *input, int *i, t_env *env_list)
{
	char	*expanded;
	char	*old;
	char    *result;

	printf("\033[32mDEBUG: handle_dollar_sign called at position %d\033[0m\n", *i);

	expanded = ft_extract_env_var(input, i, env_list);
	printf("\033[32mDEBUG: Variable expanded to '%s'\033[0m\n", expanded ? expanded : "NULL");

	old = str;
	result = ft_strjoin(str, expanded);

	printf("\033[32mDEBUG: Joined '%s' with '%s' to get '%s'\033[0m\n",
	       old ? old : "NULL", expanded ? expanded : "NULL", result ? result : "NULL");

	free(old);
	free(expanded);
	(*i)++;

	return (result);
}

static char	*handle_regular_char(char *str, char *input, int *i)
{
	char	tmp[2];
	char	*old;
	char    *result;

	tmp[0] = input[*i];
	tmp[1] = '\0';

	printf("\033[32mDEBUG: handle_regular_char called with char '%c' at position %d\033[0m\n",
	       tmp[0], *i);

	old = str;
	result = ft_strjoin(str, tmp);

	printf("\033[32mDEBUG: Joined '%s' with '%c' to get '%s'\033[0m\n",
	       old ? old : "NULL", tmp[0], result ? result : "NULL");

	free(old);
	(*i)++;

	return (result);
}

static void	skip_whitespace(char *input, int *i)
{
	int start_pos = *i;

	while (input[*i] && (input[*i] == ' ' || (input[*i] >= '\t'
				&& input[*i] <= '\r')))
		(*i)++;

	if (*i > start_pos)
		printf("\033[32mDEBUG: Skipped whitespace from position %d to %d\033[0m\n",
		       start_pos, *i);
}

char	*ft_tokenize(char *str, char *input, int *index, t_env *env_list)
{
	int		i;
	char	tmp[2];

	printf("\033[32mDEBUG: ft_tokenize called with str='%s', index=%d, input='%s'\033[0m\n",
	       str ? str : "NULL", *index, input ? input : "NULL");

	i = *index;

	// Special handling for redirection tokens
	if (input[i] == '>' || input[i] == '<')
	{
		printf("\033[32mDEBUG: Found potential redirection token at position %d\033[0m\n", i);

		if (input[i] == '>' && input[i + 1] == '>')
		{
			printf("\033[32mDEBUG: Handling >> token\033[0m\n");
			str = ft_concat_and_free(str, ft_strdup(">>"));
			*index = i + 2;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			printf("\033[32mDEBUG: Handling << token\033[0m\n");
			str = ft_concat_and_free(str, ft_strdup("<<"));
			*index = i + 2;
		}
		else
		{
			printf("\033[32mDEBUG: Handling single %c token\033[0m\n", input[i]);
			tmp[0] = input[i];
			tmp[1] = '\0';
			str = ft_concat_and_free(str, ft_strdup(tmp));
			*index = i + 1;
		}

		printf("\033[32mDEBUG: Redirection token handled, result='%s', new index=%d\033[0m\n",
		       str ? str : "NULL", *index);

		return (str);
	}

	// Handle regular tokens
	printf("\033[32mDEBUG: Handling regular token from position %d\033[0m\n", i);
	while (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			printf("\033[32mDEBUG: Found quote at position %d\033[0m\n", i);
			str = handle_quotes(str, input, &i, env_list);
		}
		else if (input[i] == '$')
		{
			printf("\033[32mDEBUG: Found $ at position %d\033[0m\n", i);
			str = handle_dollar_sign(str, input, &i, env_list);
		}
		else
		{
			str = handle_regular_char(str, input, &i);
		}

		if (!input[i])
		{
			printf("\033[32mDEBUG: End of input reached\033[0m\n");
			break;
		}
	}

	// Check if we encountered a redirection
	if (input[i] == '<' || input[i] == '>')
	{
		printf("\033[32mDEBUG: Found redirection at position %d, stopping token\033[0m\n", i);
		*index = i;
		return (str);
	}

	// Skip whitespace after the token
	skip_whitespace(input, &i);
	*index = i;

	printf("\033[32mDEBUG: ft_tokenize returning '%s', new index=%d\033[0m\n",
	       str ? str : "NULL", *index);

	return (str);
}
