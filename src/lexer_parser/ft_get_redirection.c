/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:35:43 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/05 13:21:24 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_inside_quotes(char *token)
{
	int		quote_state;
	char	current_quote;
	int		i;

	quote_state = 0;
	current_quote = 0;
	i = 0;
	while (token[i])
	{
		if (!quote_state && (token[i] == '\'' || token[i] == '"'))
		{
			quote_state = 1;
			current_quote = token[i];
		}
		else if (quote_state && token[i] == current_quote)
		{
			quote_state = 0;
			current_quote = 0;
		}
		i++;
	}
	return (quote_state);
}

int	ft_get_redirection(char *token)
{
	if (!token || is_inside_quotes(token))
		return (0);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(token, "<", 1) == 0)
		return (IN_REDIR);
	if (ft_strncmp(token, ">", 1) == 0)
		return (OUT_REDIR);
	return (0);
}
