/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewiese-m <ewiese-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:33:11 by ewiese-m          #+#    #+#             */
/*   Updated: 2025/04/07 22:16:08 by ewiese-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_quotes(char *str, char *input, int *i, t_env *env_list)
{
	return (ft_process_quotes(str, input, i, env_list));
}

static char	*handle_dollar_sign(char *str, char *input, int *i, t_env *env_list)
{
	char	*expanded;
	char	*old;

	expanded = ft_extract_env_var(input, i, env_list);
	old = str;
	str = ft_strjoin(str, expanded);
	free(old);
	free(expanded);
	(*i)++;
	return (str);
}

static char	*handle_regular_char(char *str, char *input, int *i)
{
	char	tmp[2];
	char	*old;

	tmp[0] = input[*i];
	tmp[1] = '\0';
	old = str;
	str = ft_strjoin(str, tmp);
	free(old);
	(*i)++;
	return (str);
}

static void	skip_whitespace(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || (input[*i] >= '\t'
				&& input[*i] <= '\r')))
		(*i)++;
}

char	*ft_tokenize(char *str, char *input, int *index, t_env *env_list)
{
	int		i;
	char	tmp[2];

	i = *index;
	if (input[i] == '>' || input[i] == '<')
	{
		if (input[i] == '>' && input[i + 1] == '>')
		{
			str = ft_concat_and_free(str, ft_strdup(">>"));
			*index = i + 2;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			str = ft_concat_and_free(str, ft_strdup("<<"));
			*index = i + 2;
		}
		else
		{
			tmp[0] = input[i];
			tmp[1] = '\0';
			str = ft_concat_and_free(str, ft_strdup(tmp));
			*index = i + 1;
		}
		return (str);
	}
	while (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '"' || input[i] == '\'')
			str = handle_quotes(str, input, &i, env_list);
		else if (input[i] == '$')
			str = handle_dollar_sign(str, input, &i, env_list);
		else
			str = handle_regular_char(str, input, &i);
		if (!input[i])
			break ;
	}
	if (input[i] == '<' || input[i] == '>')
	{
		*index = i;
		return (str);
	}
	skip_whitespace(input, &i);
	*index = i;
	return (str);
}
