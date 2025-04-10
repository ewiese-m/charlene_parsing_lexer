/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:35:43 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/10 13:07:11 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** This function determines if a token is likely to have come from quoted content.
** It uses multiple heuristics to make this determination:
** 1. Contains whitespace AND special shell characters (likely quoted)
** 2. Contains balanced quotes in the middle (likely quoted)
** 3. Contains multiple special characters in a pattern unlike normal shell syntax
** 4. Has length > 1 and starts with a special character followed by non-whitespace
**    (except for valid operators like >>, <<, etc.)
*/
int	was_quoted_content(char *token)
{
	int	i;
	int	has_spaces;
	int	has_special_chars;
	int	special_char_count;
	int	consecutive_special;

	printf("\033[35mDEBUG: was_quoted_content called with token = '%s'\033[0m\n", token ? token : "NULL");
	if (!token || token[0] == '\0')
		return (0);

	// Check for common redirection patterns that should NOT be treated as quoted
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0 ||
		ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0 ||
		ft_strcmp(token, "|") == 0)
	{
		printf("\033[35mDEBUG: Token is a standard operator, not quoted content\033[0m\n");
		return (0);
	}

	// If it's a single character that isn't a redirection or pipe, it's not quoted
	if (ft_strlen(token) == 1 &&
		token[0] != '>' && token[0] != '<' && token[0] != '|' &&
		token[0] != '*' && token[0] != '?' && token[0] != ';')
	{
		printf("\033[35mDEBUG: Token is a single non-special character, not quoted content\033[0m\n");
		return (0);
	}

	// Check for presence of spaces and special characters
	i = 0;
	has_spaces = 0;
	has_special_chars = 0;
	special_char_count = 0;
	consecutive_special = 0;
	while (token[i])
	{
		// Track spaces
		if (token[i] == ' ' || (token[i] >= '\t' && token[i] <= '\r'))
			has_spaces = 1;

		// Track special shell characters
		if (token[i] == '<' || token[i] == '>' ||
			token[i] == '|' || token[i] == ';' ||
			token[i] == '*' || token[i] == '?' ||
			token[i] == '[' || token[i] == ']' ||
			token[i] == '(' || token[i] == ')' ||
			token[i] == '&' || token[i] == '#')
		{
			has_special_chars = 1;
			special_char_count++;

			// Check for consecutive special characters (except valid operators)
			if (i > 0 && (token[i-1] == '<' || token[i-1] == '>' ||
				token[i-1] == '|' || token[i-1] == ';' ||
				token[i-1] == '*' || token[i-1] == '?' ||
				token[i-1] == '[' || token[i-1] == ']' ||
				token[i-1] == '(' || token[i-1] == ')' ||
				token[i-1] == '&' || token[i-1] == '#'))
			{
				// Check if it's a valid operator sequence
				if (!((token[i-1] == '>' && token[i] == '>') ||
					  (token[i-1] == '<' && token[i] == '<') ||
					  (token[i-1] == '|' && token[i] == '|') ||
					  (token[i-1] == '&' && token[i] == '&')))
				{
					consecutive_special = 1;
				}
			}
		}
		i++;
	}

	// Special case: Check for redirection operators at the start
	// If token STARTS with > or < but is more than just that operator,
	// and is NOT a valid redirection operator (>> or <<), then it's likely quoted
	if (token[0] == '>' || token[0] == '<')
	{
		// Check if it might be >> or << (valid operators)
		if (ft_strlen(token) > 2 &&
			!((token[0] == '>' && token[1] == '>') ||
			  (token[0] == '<' && token[1] == '<')))
		{
			printf("\033[35mDEBUG: Token starts with redirection but has additional content, likely quoted\033[0m\n");
			return (1);
		}
		else if (ft_strlen(token) == 2 &&
				!((token[0] == '>' && token[1] == '>') ||
				  (token[0] == '<' && token[1] == '<')))
		{
			printf("\033[35mDEBUG: Token is redirector + another char, likely quoted\033[0m\n");
			return (1);
		}
	}

	// Special case: Check for pipe at the start followed by something other than pipe
	if (token[0] == '|' && ft_strlen(token) > 1 && token[1] != '|')
	{
		printf("\033[35mDEBUG: Token starts with pipe but has additional non-pipe content, likely quoted\033[0m\n");
		return (1);
	}

	// Heuristic rules to determine if token was quoted

	// Rule 1: Contains both spaces AND special characters
	if (has_spaces && has_special_chars)
	{
		printf("\033[35mDEBUG: Token contains both spaces and special characters, likely quoted\033[0m\n");
		return (1);
	}

	// Rule 2: Contains multiple different special characters
	if (special_char_count > 2)
	{
		printf("\033[35mDEBUG: Token contains multiple special characters (%d), likely quoted\033[0m\n",
			   special_char_count);
		return (1);
	}

	// Rule 3: Contains consecutive special characters that aren't valid operators
	if (consecutive_special)
	{
		printf("\033[35mDEBUG: Token contains unusual consecutive special characters, likely quoted\033[0m\n");
		return (1);
	}

	// Check for presence of quoted characters in the middle
	i = 1;
	while (token[i] && i < (int)ft_strlen(token) - 1)
	{
		if ((token[i] == '\'' || token[i] == '"') &&
			(token[0] != token[i] && token[ft_strlen(token)-1] != token[i]))
		{
			printf("\033[35mDEBUG: Token contains quote character in the middle, likely quoted\033[0m\n");
			return (1);
		}
		i++;
	}

	printf("\033[35mDEBUG: No evidence token was quoted content, returning 0\033[0m\n");
	return (0);
}

// Get redirection type from token
int	ft_get_redirection(char *token)
{
	int result = 0;

	printf("\033[35mDEBUG: ft_get_redirection called with token = '%s'\033[0m\n",
       token ? token : "NULL");

	if (!token || was_quoted_content(token)) {
		printf("\033[35mDEBUG: Token is NULL or quoted content, not a redirection\033[0m\n");
		return (0);
	}

	if (ft_strncmp(token, ">>", 2) == 0) {
		result = APPEND;
		printf("\033[35mDEBUG: Found APPEND redirection (>>)\033[0m\n");
	}
	else if (ft_strncmp(token, "<<", 2) == 0) {
		result = HEREDOC;
		printf("\033[35mDEBUG: Found HEREDOC redirection (<<)\033[0m\n");
	}
	else if (ft_strncmp(token, "<", 1) == 0) {
		result = IN_REDIR;
		printf("\033[35mDEBUG: Found INPUT redirection (<)\033[0m\n");
	}
	else if (ft_strncmp(token, ">", 1) == 0) {
		result = OUT_REDIR;
		printf("\033[35mDEBUG: Found OUTPUT redirection (>)\033[0m\n");
	}

	printf("\033[35mDEBUG: ft_get_redirection returning %d\033[0m\n", result);
	return (result);
}
